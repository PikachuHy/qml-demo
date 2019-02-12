package com.coderising.jvm.test;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import com.coderising.jvm.engine.MiniJVM;

public class MiniJVMTest {
	
	static final String PATH = "C:\\Users\\pikachu\\Documents\\Tencent Files\\2931408816\\FileRecv\\mini-jvm-assignment\\bin";
	static final String PATH1 = "D:\\Temp";
	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testMain() throws Exception{
		String[] classPaths = {PATH1,PATH};
		MiniJVM jvm = new MiniJVM();
//		jvm.run(classPaths, "com.coderising.jvm.test.EmployeeV1");
		jvm.run(classPaths, "com.coderising.jvm.test.EmployeeV2");
//		jvm.run(classPaths, "com.coderising.jvm.test.Main");
//		jvm.run(classPaths, "com.coderising.jvm.test.HourlyEmployee");

	}

}
