package com.coderising.jvm.attr;

import com.coderising.jvm.clz.ClassFile;
import com.coderising.jvm.cmd.ByteCodeCommand;
import com.coderising.jvm.cmd.CommandParser;
import com.coderising.jvm.constant.ConstantPool;
import com.coderising.jvm.loader.ByteCodeIterator;


public class CodeAttr extends AttributeInfo {
	private int maxStack ;
	private int maxLocals ;
	private int codeLen ;
	private String code;
	public String getCode() {
		return code;
	}

	private ByteCodeCommand[] cmds ;
	public ByteCodeCommand[] getCmds() {		
		return cmds;
	}
	private LineNumberTable lineNumTable;
	private LocalVariableTable localVarTable;
	private StackMapTable stackMapTable;
	
	public CodeAttr(int attrNameIndex, int attrLen, int maxStack, int maxLocals, int codeLen,String code ,ByteCodeCommand[] cmds) {
		super(attrNameIndex, attrLen);
		this.maxStack = maxStack;
		this.maxLocals = maxLocals;
		this.codeLen = codeLen;
		this.code = code;
		this.cmds = cmds;
	}

	public void setLineNumberTable(LineNumberTable t) {
		this.lineNumTable = t;
	}

	public void setLocalVariableTable(LocalVariableTable t) {
		this.localVarTable = t;		
	}
	
	public static CodeAttr parse(ClassFile clzFile, ByteCodeIterator iter){
		iter.back(2);
		int attrNameIndex = iter.nextU2ToInt();
		int attrLen = iter.nextU4ToInt();
		int maxStack = iter.nextU2ToInt();
		int maxLocals = iter.nextU2ToInt();
		int codeLen = iter.nextU4ToInt();
		String code = iter.nextUxToHexString(codeLen);
		// 将字节码解析为指令
		ByteCodeCommand[] cmds = CommandParser.parse(clzFile,code);
		CodeAttr attr = new CodeAttr(attrNameIndex,attrLen,maxStack,maxLocals,codeLen,code,cmds);
		int exceptionTableLen = iter.nextU2ToInt();
		if(exceptionTableLen>0){
			throw new RuntimeException("Exception Table has not been implemented");
		}
		// 这个地方很坑啊
		int attrCount = iter.nextU2ToInt();
		for (int i = 0; i < attrCount; i++) {
			int attrNameIndex2 = iter.nextU2ToInt();
			String name = clzFile.getConstantPool().getUTF8String(attrNameIndex2);
//			System.out.println("attrNameIndex:"+attrNameIndex2+"\tname:"+name);
			switch (name){
				case AttributeInfo.CODE:{
					CodeAttr attr2 = CodeAttr.parse(clzFile, iter);
//					method.setCodeAttr(attr);
					break;
				}
				case AttributeInfo.LINE_NUM_TABLE:{
					LineNumberTable table = LineNumberTable.parse(iter);
					attr.setLineNumberTable(table);
					break;
				}
				case AttributeInfo.LOCAL_VAR_TABLE:{
					LocalVariableTable table = LocalVariableTable.parse(iter);
					attr.setLocalVariableTable(table);
					break;
				}
				case AttributeInfo.STACK_MAP_TABLE:{
					// 这里难道不需要回退？
					StackMapTable table = StackMapTable.parse(iter);
					attr.setStackMapTable(table);
					break;
				}
				default:{
					throw new RuntimeException("Unimplement attribute "+name);
				}
			}
		}
		return attr;
	}
	

	public String toString(ConstantPool pool){
		StringBuilder buffer = new StringBuilder();
		//buffer.append("Code:").append(code).append("\n");
		for(int i=0;i<cmds.length;i++){
			buffer.append(cmds[i].toString(pool)).append("\n");
		}
		buffer.append("\n");
		buffer.append(this.lineNumTable.toString());
		buffer.append(this.localVarTable.toString(pool));
		return buffer.toString();
	}
	private void setStackMapTable(StackMapTable t) {
		this.stackMapTable = t;
		
	}

	
	
	
	
}
