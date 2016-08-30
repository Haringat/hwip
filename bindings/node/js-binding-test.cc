#include <node.h>
#include <string>
#include <sstream>

namespace footest {

using namespace v8;
 
void fooWrapper(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	if(args.Length() < 1){
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "test requires 1 argument. 0 given.")));
	}
	String arg0;
	if(args[0]->IsString()){
		String arg0 = args[0]->ToString();
	}
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, "test"));
}

void init(Local<Object> exports) {
	NODE_SET_METHOD(exports, "test", fooWrapper);
}

NODE_MODULE(footest, init)
}
