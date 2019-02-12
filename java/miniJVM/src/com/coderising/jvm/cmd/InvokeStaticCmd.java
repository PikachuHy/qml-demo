package com.coderising.jvm.cmd;

import com.coderising.jvm.clz.ClassFile;
import com.coderising.jvm.constant.ConstantPool;
import com.coderising.jvm.constant.MethodRefInfo;
import com.coderising.jvm.engine.ExecutionResult;
import com.coderising.jvm.engine.MethodArea;
import com.coderising.jvm.engine.StackFrame;
import com.coderising.jvm.method.Method;

public class InvokeStaticCmd extends TwoOperandCmd {
    public InvokeStaticCmd(ClassFile clzFile, String opCode) {
        super(clzFile, opCode);
    }

    @Override
    public String toString(ConstantPool pool) {
        return super.getOperandAsMethod(pool);
    }

    @Override
    public void execute(StackFrame frame, ExecutionResult result) {
        MethodRefInfo methodRefInfo = (MethodRefInfo) getConstantInfo(getIndex());

        Method m = MethodArea.getInstance().getMethod(methodRefInfo);
        result.setNextAction(ExecutionResult.PAUSE_AND_RUN_NEW_FRAME);
        result.setNextMethod(m);
    }
}
