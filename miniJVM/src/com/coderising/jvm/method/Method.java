package com.coderising.jvm.method;

import com.coderising.jvm.clz.ClassFile;
import com.coderising.jvm.cmd.ByteCodeCommand;
import com.coderising.jvm.attr.AttributeInfo;
import com.coderising.jvm.attr.CodeAttr;
import com.coderising.jvm.constant.ConstantPool;
import com.coderising.jvm.constant.UTF8Info;
import com.coderising.jvm.loader.ByteCodeIterator;

import java.util.LinkedList;
import java.util.List;


public class Method {
	
	private int accessFlag;
	private int nameIndex;
	private int descriptorIndex;
	
	private CodeAttr codeAttr;
	
	private ClassFile clzFile;
	
	
	public ClassFile getClzFile() {
		return clzFile;
	}

	public int getNameIndex() {
		return nameIndex;
	}
	public int getDescriptorIndex() {
		return descriptorIndex;
	}
	
	public CodeAttr getCodeAttr() {
		return codeAttr;
	}

	public void setCodeAttr(CodeAttr code) {
		this.codeAttr = code;
	}
	
	

	public Method(ClassFile clzFile,int accessFlag, int nameIndex, int descriptorIndex) {
		this.clzFile = clzFile;
		this.accessFlag = accessFlag;
		this.nameIndex = nameIndex;
		this.descriptorIndex = descriptorIndex;
	}

	
	
	
	
	public String toString() {
		
		ConstantPool pool = this.clzFile.getConstantPool();
		StringBuilder buffer = new StringBuilder();
		
		String name = ((UTF8Info)pool.getConstantInfo(this.nameIndex)).getValue();
		
		String desc = ((UTF8Info)pool.getConstantInfo(this.descriptorIndex)).getValue();
		
		buffer.append(name).append(":").append(desc).append("\n");
		
		buffer.append(this.codeAttr.toString(pool));
		
		return buffer.toString();
	}
	
	public static Method parse(ClassFile clzFile, ByteCodeIterator iter){
		int accessFlag = iter.nextU2ToInt();
		int nameIndex = iter.nextU2ToInt();
		int descIndex = iter.nextU2ToInt();
		int attribCount = iter.nextU2ToInt();
//		System.out.println("method attriubte count:"+attribCount);
		Method method = new Method(clzFile,accessFlag,nameIndex,descIndex);
		for (int i = 0; i < attribCount; i++) {
			int attrNameIndex = iter.nextU2ToInt();
			String name = clzFile.getConstantPool().getUTF8String(attrNameIndex);
//			System.out.println("attrNameIndex:"+attrNameIndex+"\tname:"+name);
			switch (name){
				case AttributeInfo.CODE:{
					CodeAttr attr = CodeAttr.parse(clzFile, iter);
					method.setCodeAttr(attr);
					break;
				}
				default:{
					throw new RuntimeException("Unimplement attribute "+name);
				}
			}
		}
		/*
		if(attribCount > 0){
			throw new RuntimeException("Method Attribute has not been implemented");
		}
		*/
		return method;
		
	}

	public ByteCodeCommand[] getCmds() {		
		return this.getCodeAttr().getCmds();
	}

	public String getParamAndReturnType(){
		UTF8Info info = (UTF8Info) clzFile.getConstantPool().getConstantInfo(descriptorIndex);
		return info.getValue();
	}
	public List<String> getParameterList(){
		// 拿到方法的签名,比如：(Ljava/util/List;Ljava/lang/String;II)V
		String paramAndType = getParamAndReturnType();
		// 去掉括号
		int first = paramAndType.indexOf("(");
		int last = paramAndType.indexOf(")");
		String param = paramAndType.substring(first+1,last);

		List<String> list = new LinkedList<>();
		if(param==null || "".equals(param)){
			return list;
		}
		while (!param.equals("")){
			int pos = 0;
			if(param.charAt(pos)=='L'){
				int end = param.indexOf(";");
				if (end == -1){
					throw new RuntimeException("param error: "+param);
				}
				list.add(param.substring(0,end));
				param = param.substring(end+1);
			}else if(param.charAt(pos)=='I'){
				list.add("I");
				param = param.substring(pos+1);
			}else {
				throw new RuntimeException("Unsupport Type: "+param);
			}
		}
		return list;
	}
}
