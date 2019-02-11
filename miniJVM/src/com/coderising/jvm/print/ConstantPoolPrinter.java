package com.coderising.jvm.print;

import com.coderising.jvm.constant.ClassInfo;
import com.coderising.jvm.constant.ConstantInfo;
import com.coderising.jvm.constant.ConstantPool;
import com.coderising.jvm.constant.FieldRefInfo;
import com.coderising.jvm.constant.MethodRefInfo;
import com.coderising.jvm.constant.NameAndTypeInfo;
import com.coderising.jvm.constant.StringInfo;
import com.coderising.jvm.constant.UTF8Info;

public class ConstantPoolPrinter {
	ConstantPool pool;
	ConstantPoolPrinter(ConstantPool pool){
		this.pool = pool;
	}
	public void print(){
		String formatType = "%-20s";
		String formatIndex = "%-20s";
		System.out.println("Constant Pool:");

		ConstantInfo.Visitor visitor = new ConstantInfo.Visitor() {
			@Override
			public void visitClassInfo(ClassInfo info) {
				System.out.printf(formatType,"Class");
				System.out.printf(formatIndex,"#"+info.getUtf8Index());
				System.out.print("// "+info.getClassName());
			}

			@Override
			public void visitFieldRef(FieldRefInfo info) {
				System.out.printf(formatType,"Fieldref");
				System.out.printf(formatIndex,"#"+info.getClassInfoIndex()+".#"+info.getNameAndTypeIndex());
				System.out.print("// "+info.getFieldName()+":"+info.getClassName());
			}

			@Override
			public void visitMethodRef(MethodRefInfo info) {
				System.out.printf(formatType,"Methodref");
				System.out.printf(formatIndex,"#"+info.getClassInfoIndex()+".#"+info.getNameAndTypeIndex());
				System.out.print("// "+info.getClassName()+"."+info.getMethodName()+":"+info.getParamAndReturnType());
			}

			@Override
			public void visitNameAndType(NameAndTypeInfo info) {
				System.out.printf(formatType,"NameAndType");
				System.out.printf(formatIndex,"#"+info.getIndex1()+":#"+info.getIndex2());
				System.out.print("// "+info.getName()+":"+info.getTypeInfo());
			}

			@Override
			public void visitString(StringInfo info) {
				System.out.printf(formatType,"String");
				System.out.printf(formatIndex,"#"+info.getIndex());
				UTF8Info t = (UTF8Info) info.getConstantInfo(info.getIndex());
				System.out.print("// "+t.getValue());
			}

			@Override
			public void visistUTF8(UTF8Info info) {
				System.out.printf(formatType,"Utf8");
				System.out.print(info.getValue());
			}
		};
		for (int i = 1; i <= pool.getSize(); i++) {
			System.out.printf("%4s = ","#"+i);
			pool.getConstantInfo(i).accept(visitor);
			System.out.println();
		}
		
	}
}
