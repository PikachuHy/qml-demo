package com.coderising.jvm.loader;

import java.io.UnsupportedEncodingException;

import com.coderising.jvm.clz.AccessFlag;
import com.coderising.jvm.clz.ClassFile;
import com.coderising.jvm.clz.ClassIndex;
import com.coderising.jvm.constant.*;
import com.coderising.jvm.field.Field;
import com.coderising.jvm.method.Method;

public class ClassFileParser {

	public ClassFile parse(byte[] codes) {
		ByteCodeIterator iter = new ByteCodeIterator(codes);
		String magicNumber = iter.nextU4ToHexString();
		if(!magicNumber.equals("cafebabe")){
			return null;
		}
		ClassFile classFile = new ClassFile();
		classFile.setMinorVersion(iter.nextU2ToInt());
		classFile.setMajorVersion(iter.nextU2ToInt());
		ConstantPool pool = parseConstantPool(iter);
		classFile.setConstPool(pool);
		classFile.setAccessFlag(parseAccessFlag(iter));
		classFile.setClassIndex(parseClassInfex(iter));
		parseInterfaces(iter);
		parseFileds(classFile,iter);
		parseMethods(classFile,iter);
		return classFile;
	}

	private AccessFlag parseAccessFlag(ByteCodeIterator iter) {
		AccessFlag flag = new AccessFlag(iter.nextU2ToInt());
		return flag;
	}

	private ClassIndex parseClassInfex(ByteCodeIterator iter) {
		ClassIndex classIndex = new ClassIndex();
		classIndex.setThisClassIndex(iter.nextU2ToInt());
		classIndex.setSuperClassIndex(iter.nextU2ToInt());
		return classIndex;

	}

	private ConstantPool parseConstantPool(ByteCodeIterator iter) {
		ConstantPool pool = new ConstantPool();
		int size = iter.nextU2ToInt();
		pool.addConstantInfo(new NullConstantInfo());
		for (int i = 0; i < size-1; i++) {
			int tag = iter.nextU1toInt();
			switch (tag){
				case ConstantInfo.UTF8_INFO:{
					UTF8Info info = new UTF8Info(pool);
					info.setLength(iter.nextU2ToInt());
					info.setValue(iter.nextUxToString(info.getLength()));
					pool.addConstantInfo(info);
					break;
				}
				case ConstantInfo.FLOAT_INFO:{

					break;
				}
				case ConstantInfo.CLASS_INFO:{
					ClassInfo info = new ClassInfo(pool);
					info.setUtf8Index(iter.nextU2ToInt());
					pool.addConstantInfo(info);
					break;
				}
				case ConstantInfo.STRING_INFO:{
					StringInfo info = new StringInfo(pool);
					info.setIndex(iter.nextU2ToInt());
					pool.addConstantInfo(info);
					break;
				}
				case ConstantInfo.FIELD_INFO:{
					FieldRefInfo info = new FieldRefInfo(pool);
					info.setClassInfoIndex(iter.nextU2ToInt());
					info.setNameAndTypeIndex(iter.nextU2ToInt());
					pool.addConstantInfo(info);
					break;
				}
				case ConstantInfo.METHOD_INFO:{
					MethodRefInfo info = new MethodRefInfo(pool);
					info.setClassInfoIndex(iter.nextU2ToInt());
					info.setNameAndTypeIndex(iter.nextU2ToInt());
					pool.addConstantInfo(info);
					break;
				}
				case ConstantInfo.NAME_AND_TYPE_INFO:{
					NameAndTypeInfo info = new NameAndTypeInfo(pool);
					info.setIndex1(iter.nextU2ToInt());
					info.setIndex2(iter.nextU2ToInt());
					pool.addConstantInfo(info);
					break;
				}
				default:{
					throw new RuntimeException("Unsupport tag:"+tag+"; It may support later");
				}
			}
		}
		return pool;
	}
	private void parseInterfaces(ByteCodeIterator iter) {
		int interfaceCount = iter.nextU2ToInt();

		System.out.println("interfaceCount:" + interfaceCount);

		// TODO : 如果实现了interface, 这里需要解析
	}

	private void parseFileds(ClassFile clzFile, ByteCodeIterator iter) {
		int size = iter.nextU2ToInt();
//		System.out.println("field count:"+size);
		for (int i = 0; i < size; i++) {
			clzFile.addField(Field.parse(clzFile.getConstantPool(),iter));
		}

	}

	private void parseMethods(ClassFile clzFile, ByteCodeIterator iter) {
		int size = iter.nextU2ToInt();
//		System.out.println("methods count:"+size);
		for (int i = 0; i < size; i++) {
			clzFile.addMethod(Method.parse(clzFile,iter));
		}

	}
	
}
