package com.coderising.jvm.cmd;

import com.coderising.jvm.clz.ClassFile;
import com.coderising.jvm.constant.ConstantPool;
import com.coderising.jvm.constant.MethodRefInfo;
import com.coderising.jvm.constant.StringInfo;
import com.coderising.jvm.engine.ExecutionResult;
import com.coderising.jvm.engine.JavaObject;
import com.coderising.jvm.engine.MethodArea;
import com.coderising.jvm.engine.StackFrame;
import com.coderising.jvm.method.Method;


public class InvokeVirtualCmd extends TwoOperandCmd {

	public InvokeVirtualCmd(ClassFile clzFile,String opCode) {
		super(clzFile,opCode);
	}

	@Override
	public String toString(ConstantPool pool) {
		
		return super.getOperandAsMethod(pool);
	}

	public boolean isSystemOutPrintlnMethod(String className, String methodName){
	    return "java/io/PrintStream".equals(className)
                && "println".equals(methodName);
    }
	@Override
	public void execute(StackFrame frame, ExecutionResult result) {
		System.out.println("execute");
		MethodRefInfo methodRefInfo = (MethodRefInfo) getConstantInfo(getIndex());
        String className = methodRefInfo.getClassName();
        String methodName = methodRefInfo.getMethodName();
        if(isSystemOutPrintlnMethod(className,methodName)){
            JavaObject javaObject = frame.getOprandStack().pop();
            String value = javaObject.toString();
            System.err.print("----------------------");
            System.err.print(value);
            System.err.println("----------------------");
            return;
        }
        // 实现多态
        JavaObject javaObject = frame.getOprandStack().peek();
        MethodArea methodArea = MethodArea.getInstance();
        Method method = null;
        String currentClassName = javaObject.getClassName();
        while (currentClassName!=null){
            ClassFile currentClassFile = methodArea.findClassFile(currentClassName);
            method = currentClassFile.getMethod(methodRefInfo.getMethodName(),methodRefInfo.getParamAndReturnType());
            if (method!=null){
                break;
            }else {
                currentClassName = currentClassFile.getSuperClassName();
            }
        }
        if (method==null){
            throw new RuntimeException("Can't find method for: "+methodRefInfo);
        }
        result.setNextAction(ExecutionResult.PAUSE_AND_RUN_NEW_FRAME);
        result.setNextMethod(method);
        /*
        // 没有多态
        Method method = MethodArea.getInstance().getMethod(methodRefInfo);
        if(method==null){
            throw new RuntimeException(className+" "+methodName+" has not implement");
        }else {
            result.setNextAction(ExecutionResult.PAUSE_AND_RUN_NEW_FRAME);
            result.setNextMethod(method);
        }
        */
    }

	
	

}
