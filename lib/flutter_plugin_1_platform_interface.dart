import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'flutter_plugin_1_pigeon.dart';

abstract class FlutterPlugin_1Platform extends PlatformInterface {
  /// Constructs a FlutterPlugin_1Platform.
  FlutterPlugin_1Platform() : super(token: _token);

  static final Object _token = Object();

  static FlutterPlugin_1Platform _instance = FlutterPlugin1Pigeon();

  /// The default instance of [FlutterPlugin_1Platform] to use.
  ///
  /// Defaults to [MethodChannelFlutterPlugin_1].
  static FlutterPlugin_1Platform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FlutterPlugin_1Platform] when
  /// they register themselves.
  static set instance(FlutterPlugin_1Platform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
