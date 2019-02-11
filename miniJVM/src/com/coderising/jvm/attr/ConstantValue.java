package com.coderising.jvm.attr;

import com.coderising.jvm.clz.ClassFile;
import com.coderising.jvm.constant.ConstantPool;
import com.coderising.jvm.loader.ByteCodeIterator;

public class ConstantValue extends AttributeInfo {
    private int valueIndex;
    public ConstantValue(int attrNameIndex, int attrLen) {
        super(attrNameIndex, attrLen);
    }

    public int getValueIndex() {
        return valueIndex;
    }

    public void setValueIndex(int valueIndex) {
        this.valueIndex = valueIndex;
    }
    public static ConstantValue parse(ConstantPool pool, ByteCodeIterator iter){
        iter.back(2);
        int attrNameIndex = iter.nextU2ToInt();
        int attrLen = iter.nextU4ToInt();
        ConstantValue constantValue = new ConstantValue(attrNameIndex,attrLen);
        constantValue.setValueIndex(iter.nextU2ToInt());
        return constantValue;
    }
}
