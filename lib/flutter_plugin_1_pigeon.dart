import 'package:flutter/foundation.dart';

import 'flutter_plugin_1_platform_interface.dart';
import 'src/messages.g.dart';

/// An implementation of [FlutterPlugin_1Platform] that uses method channels.
class FlutterPlugin1Pigeon extends FlutterPlugin_1Platform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final api = MyHostApi();

  @override
  Future<String?> getPlatformVersion() async {
    // final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    // return version;
    final result = await api.doThing(42);

    for (final element in result) {
      print('Result from native: $element');
    }

    return null;
  }
}
