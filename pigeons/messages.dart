import 'package:pigeon/pigeon.dart';
@ConfigurePigeon(
  PigeonOptions(
    dartPackageName: 'flutter_plugin_1',
    dartOut: 'lib/src/messages.g.dart',
    gobjectHeaderOut: 'linux/messages.g.h',
    gobjectSourceOut: 'linux/messages.g.cc',
  ),
)
@HostApi()
abstract class MyHostApi {
  List<MyClass> doThing(int myNumber);
}

class MyClass {
  final Uint8List intList;

  MyClass({required this.intList});
}
