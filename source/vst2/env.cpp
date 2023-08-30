#if defined(AUDIOPLUGIN_BACKEND_VST2)

#include <vst2/env.hpp>

namespace audioplugin {
namespace validate {

    namespace {

        VstIntPtr host_callback(AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt)
        {
            VstIntPtr result = 0;

            // Filter idle calls...
            bool filtered = false;
            if (opcode == audioMasterIdle) {
                static bool wasIdle = false;
                if (wasIdle)
                    filtered = true;
                else {
                    printf("(Future idle calls will not be displayed!)\n");
                    wasIdle = true;
                }
            }

            // if (!filtered)
            //     printf("PLUG> HostCallback (opcode %d)\n index = %d, value = %p, ptr = %p, opt = %f\n", opcode, index, FromVstPtr<void>(value), ptr, opt);

            switch (opcode) {
            case audioMasterVersion:
                result = kVstVersion;
                break;
            }

            return result;
        }
    }

    plugin_data::~plugin_data()
    {
    }

    plugin_data::plugin_data(const dylib& library)
    {
        try {

            using vst2_entry_function = AEffect* (*)(audioMasterCallback);
            vst2_entry_function _vst2_plugin_main = nullptr;
            try {
                _vst2_plugin_main = library.get_function<AEffect*(audioMasterCallback)>("VSTPluginMain");
                std::cout << "[==========] Found VSTPluginMain" << std::endl;
            } catch (...) {
                std::cout << "[----------] AEffect* VSTPluginMain(audioMasterCallback) not found" << std::endl;
                try {
                    _vst2_plugin_main = library.get_function<AEffect*(audioMasterCallback)>("main"); // main_macho on macos
                    std::cout << "[==========] Found main" << std::endl;
                } catch (...) {
                    throw std::exception("AEffect* main(audioMasterCallback) not found");
                }
            }

            data = _vst2_plugin_main(audioplugin::validate::host_callback);
            if (!data) {
                printf("Failed to create effect instance!\n");
                // return 1;
            }
            std::size_t _inputs_count = static_cast<std::size_t>(data->numInputs);
            std::cout << "[----------] Found " << std::to_string(_inputs_count) << " audio inputs" << std::endl;

            std::size_t _outputs_count = static_cast<std::size_t>(data->numOutputs);
            std::cout << "[----------] Found " << std::to_string(_outputs_count) << " audio outputs" << std::endl;

            data->processDoubleReplacing(data, nullptr, nullptr, 10);

            bool _effect_is_synth = data->flags & VstAEffectFlags::effFlagsIsSynth;
            std::cout << "[----------] Effect is synth : " << std::boolalpha << _effect_is_synth << std::endl;

            bool _effect_has_editor = data->flags & VstAEffectFlags::effFlagsHasEditor;
            std::cout << "[----------] Effect has an editor : " << std::boolalpha << _effect_has_editor << std::endl;

            bool _effect_has_double_replacing = data->flags & VstAEffectFlags::effFlagsCanDoubleReplacing;
            std::cout << "[----------] Effect has double replacing : " << std::boolalpha << _effect_has_double_replacing << std::endl;

            // auto* ooo2 = plugin_library.value().get_function<Steinberg::IPluginFactory*()>("GetPluginFactory");

        } catch (const std::exception& _exception) {
            std::cout << "[==========] Exception occured in validator executable :" << std::endl;
            std::cout << "[==========] " << _exception.what() << std::endl;
        }
    }

	bool plugin_data::is_loaded() const
	{
		return data != nullptr;
	}
}
}

#endif