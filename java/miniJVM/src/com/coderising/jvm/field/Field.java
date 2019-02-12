package com.coderising.jvm.field;

import com.coderising.jvm.attr.AttributeInfo;
import com.coderising.jvm.attr.CodeAttr;
import com.coderising.jvm.attr.ConstantValue;
import com.coderising.jvm.constant.ConstantPool;
import com.coderising.jvm.constant.StringInfo;
import com.coderising.jvm.constant.UTF8Info;
import com.coderising.jvm.loader.ByteCodeIterator;
import com.sun.org.apache.bcel.internal.classfile.Code;

import java.util.LinkedList;
import java.util.List;


public class Field {
	private int accessFlag;
	private int nameIndex;
	private int descriptorIndex;
	// 先这样设计,可能不需要这样
	private List<AttributeInfo> attrs = new LinkedList<>();
	
	
	private ConstantPool pool;
	
	public Field( int accessFlag, int nameIndex, int descriptorIndex,ConstantPool pool) {
		
		this.accessFlag = accessFlag;
		this.nameIndex = nameIndex;
		this.descriptorIndex = descriptorIndex;
		this.pool = pool;
	}

	public String toString() {
		String name = ((UTF8Info)pool.getConstantInfo(this.nameIndex)).getValue();
		
		String desc = ((UTF8Info)pool.getConstantInfo(this.descriptorIndex)).getValue();
		return name +":"+ desc;
	}
	
	
	public static Field parse(ConstantPool pool,ByteCodeIterator iter){
		
		int accessFlag = iter.nextU2ToInt();
		int nameIndex = iter.nextU2ToInt();
		int descIndex = iter.nextU2ToInt();
		int attribCount = iter.nextU2ToInt();
//		System.out.println("field attribute count:"+ attribCount);
		
		Field f = new Field(accessFlag, nameIndex, descIndex,pool);
		for (int i = 0; i < attribCount; i++) {
			int attrNameIndex = iter.nextU2ToInt();
			String name = pool.getUTF8String(attrNameIndex);
			switch (name){
				case AttributeInfo.CONST_VALUE:{
                    ConstantValue info = ConstantValue.parse(pool,iter);
                    f.addAttr(info);
					break;
				}
				default:{
					throw new RuntimeException("Unimplement attribute "+name);
				}
			}
		}
		/*
		if(attribCount > 0){
			throw new RuntimeException("Field Attribute has not been implemented");
		}
		*/
		return f;
	}

	public void addAttr(AttributeInfo info){
	    attrs.add(info);
    }
}
