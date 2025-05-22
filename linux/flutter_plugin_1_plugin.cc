#include "include/flutter_plugin_1/flutter_plugin_1_plugin.h"

#include "messages.g.h"

#include <cstdio>
#include <flutter_linux/flutter_linux.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>
#include <vector>

#include "flutter_plugin_1_plugin_private.h"

#define FLUTTER_PLUGIN_1_PLUGIN(obj)                                           \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), flutter_plugin_1_plugin_get_type(),       \
                              FlutterPlugin_1Plugin))

struct _FlutterPlugin_1Plugin {
  GObject parent_instance;

  FlPluginRegistrar *registrar;
};

G_DEFINE_TYPE(FlutterPlugin_1Plugin, flutter_plugin_1_plugin,
              g_object_get_type())

FlutterPlugin1MyHostApiDoThingResponse *
flutter_plugin_1_plugin_handle_do_thing(int64_t my_number, gpointer user_data) {

  g_autoptr(FlValue) my_class_list = fl_value_new_list();
  std::vector<uint8_t> myVec{0, 1};
  g_autoptr(FlutterPlugin1MyClass) myClassPtr =
      flutter_plugin1_my_class_new(myVec.data(), myVec.size());

  g_autoptr(FlValue) my_class_fl =
      fl_value_new_custom_object(129, G_OBJECT(myClassPtr));
  fl_value_append(my_class_list, my_class_fl);

  return flutter_plugin1_my_host_api_do_thing_response_new(my_class_list);
}

static void flutter_plugin_1_plugin_dispose(GObject *object) {
  FlutterPlugin_1Plugin *self = FLUTTER_PLUGIN_1_PLUGIN(object);
  flutter_plugin1_my_host_api_clear_method_handlers(
      fl_plugin_registrar_get_messenger(self->registrar), nullptr);
  g_clear_object(&self->registrar);

  G_OBJECT_CLASS(flutter_plugin_1_plugin_parent_class)->dispose(object);
}

static void
flutter_plugin_1_plugin_class_init(FlutterPlugin_1PluginClass *klass) {
  G_OBJECT_CLASS(klass)->dispose = flutter_plugin_1_plugin_dispose;
}

FlutterPlugin_1Plugin *flutter_plugin_1_new(FlPluginRegistrar *registrar) {
  FlutterPlugin_1Plugin *plugin = FLUTTER_PLUGIN_1_PLUGIN(
      g_object_new(flutter_plugin_1_plugin_get_type(), nullptr));

  plugin->registrar = registrar;
  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  static FlutterPlugin1MyHostApiVTable flutter_plugin_1_api_vtable = {
      .do_thing = flutter_plugin_1_plugin_handle_do_thing};

  flutter_plugin1_my_host_api_set_method_handlers(
      fl_plugin_registrar_get_messenger(registrar), nullptr,
      &flutter_plugin_1_api_vtable, g_object_ref(plugin), g_object_unref);

  return plugin;
}

static void flutter_plugin_1_plugin_init(FlutterPlugin_1Plugin *self) {}

void flutter_plugin_1_plugin_register_with_registrar(
    FlPluginRegistrar *registrar) {
  FlutterPlugin_1Plugin *plugin = flutter_plugin_1_new(registrar);
  g_object_unref(plugin);
}
