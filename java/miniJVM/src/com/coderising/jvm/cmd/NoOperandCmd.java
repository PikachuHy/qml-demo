package com.coderising.jvm.cmd;

import com.coderising.jvm.clz.ClassFile;
import com.coderising.jvm.constant.ConstantPool;
import com.coderising.jvm.engine.ExecutionResult;
import com.coderising.jvm.engine.Heap;
import com.coderising.jvm.engine.JavaObject;
import com.coderising.jvm.engine.StackFrame;

public class NoOperandCmd extends ByteCodeCommand{

	public NoOperandCmd(ClassFile clzFile, String opCode) {
		super(clzFile, opCode);
	}

	@Override
	public String toString(ConstantPool pool) {
		return this.getOffset()+":" +this.getOpCode() + " "+ this.getReadableCodeText();
	}

	
	
	public  int getLength(){
		return 1;
	}

	@Override
	public void execute(StackFrame frame, ExecutionResult result) {
		switch (opCode){
            case CommandParser.dup:{
                JavaObject javaObject = frame.getOprandStack().peek();
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.aload_0:{
                JavaObject javaObject = frame.getLocalVariableValue(0);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.iload_1:
            case CommandParser.aload_1:{
                JavaObject javaObject = frame.getLocalVariableValue(1);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.iload_2:
            case CommandParser.aload_2:{
                JavaObject javaObject = frame.getLocalVariableValue(2);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.istore_1:
            case CommandParser.astore_1:{
                JavaObject javaObject = frame.getOprandStack().pop();
                frame.setLocalVariableValue(1,javaObject);
                break;
            }
            case CommandParser.istore_2:{
                JavaObject javaObject = frame.getOprandStack().pop();
                frame.setLocalVariableValue(2,javaObject);
                break;
            }
            case CommandParser.ireturn:{
                JavaObject javaObject = frame.getOprandStack().pop();
//                frame.getOprandStack().push(javaObject);
                frame.getCallerFrame().getOprandStack().push(javaObject);
                result.setNextAction(ExecutionResult.EXIT_CURRENT_FRAME);
                break;
            }
            case CommandParser.voidreturn:{
                result.setNextAction(ExecutionResult.EXIT_CURRENT_FRAME);
                break;
            }
            case CommandParser.aconst_null:{
                frame.getOprandStack().push(null);
                break;
            }
            case CommandParser.iconst_m1:{
                JavaObject javaObject = Heap.getInstance().newInt(-1);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.iconst_0:{
                JavaObject javaObject = Heap.getInstance().newInt(0);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.iconst_1:{
                JavaObject javaObject = Heap.getInstance().newInt(1);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.iconst_2:{
                JavaObject javaObject = Heap.getInstance().newInt(2);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.iconst_3:{
                JavaObject javaObject = Heap.getInstance().newInt(3);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.iconst_4:{
                JavaObject javaObject = Heap.getInstance().newInt(4);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.iconst_5:{
                JavaObject javaObject = Heap.getInstance().newInt(5);
                frame.getOprandStack().push(javaObject);
                break;
            }
            case CommandParser.iadd:{
                JavaObject intValue1 = frame.getOprandStack().pop();
                JavaObject intValue2 = frame.getOprandStack().pop();
                JavaObject retValue = Heap.getInstance().newInt(intValue1.getIntValue()+intValue2.getIntValue());
                frame.getOprandStack().push(retValue);
                break;
            }
            default:{
                throw new RuntimeException("Cmd has not been implement: "+opCode);
            }
		}
		
	}

}
