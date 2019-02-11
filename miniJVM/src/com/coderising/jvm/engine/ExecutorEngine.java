package com.coderising.jvm.engine;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

import com.coderising.jvm.attr.CodeAttr;
import com.coderising.jvm.clz.ClassFile;
import com.coderising.jvm.cmd.ByteCodeCommand;
import com.coderising.jvm.constant.MethodRefInfo;
import com.coderising.jvm.method.Method;

public class ExecutorEngine {

	private Stack<StackFrame> stack = new Stack<StackFrame>();
	
	public ExecutorEngine() {
		
	}
	
	public void execute(Method mainMethod){
		stack.push(StackFrame.create(mainMethod));
		while (!stack.isEmpty()){
			StackFrame frame = stack.peek();
//			System.out.println(frame.getMethod().toString());
			ExecutionResult result = frame.execute();
			if(result.isExitCurrentFrame()){
				stack.pop();
			}else if(result.isPauseAndRunNewFrame()){
				Method m = result.getNextMethod();
				StackFrame stackFrame = StackFrame.create(m);
				stackFrame.setCallerFrame(frame);
				// 参数传递
				setupFunctionCallParams(frame,stackFrame);
				stack.push(stackFrame);
			}
		}
		
		
	}
	
	
	
	private void setupFunctionCallParams(StackFrame currentFrame,StackFrame nextFrame) {
		Method m = nextFrame.getMethod();
		List<String> paramList = m.getParameterList();
		// 需要传递this, 所有要加1
		int paramNum = paramList.size() + 1;


		List<JavaObject> values = new ArrayList<>();
		while (paramNum>0){
			values.add(currentFrame.getOprandStack().pop());
			paramNum--;
		}
		List<JavaObject> params = new ArrayList<>();
		for (int i = values.size()-1; i >= 0; i--) {
			params.add(values.get(i));
		}
		nextFrame.setLocalVariableTable(params);
	}
	
}
