package com.coderising.jvm.cmd;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import com.coderising.jvm.clz.ClassFile;

public class CommandParser {
	
	public static final String aconst_null = "01";
	public static final String iconst_m1 = "02";
	public static final String iconst_0 = "03";
	public static final String iconst_1 = "04";
	public static final String iconst_2 = "05";
	public static final String iconst_3 = "06";
	public static final String iconst_4 = "07";
	public static final String iconst_5 = "08";
	public static final String new_object = "BB";
	public static final String lstore = "37";
	public static final String invokestatic = "B8";
	public static final String invokespecial = "B7";
	public static final String invokevirtual = "B6";
	public static final String getfield = "B4";
	public static final String putfield = "B5";
	public static final String getstatic = "B2";
	public static final String ldc = "12";
	public static final String dup = "59";
	public static final String bipush = "10";
	public static final String aload_0 = "2A";
	public static final String aload_1 = "2B";
	public static final String aload_2 = "2C";
	public static final String iload = "15";
	public static final String iload_1 = "1B";
	public static final String iload_2 = "1C";
	public static final String iload_3 = "1D";
	public static final String fload_3 = "25";

	public static final String voidreturn = "B1";
	public static final String ireturn = "AC";
	public static final String freturn = "AE";

	public static final String astore_1 = "4C";
	public static final String if_icmp_ge = "A2";
	public static final String if_icmple = "A4";
	public static final String goto_no_condition = "A7";
	public static final String istore_1 = "3C";
	public static final String istore_2 = "3D";
	public static final String iadd = "60";
	public static final String iinc = "84";

	public static ByteCodeCommand[] parse(ClassFile clzFile, String codes) {
		List<ByteCodeCommand> commands = new LinkedList<>();
		CommandIterator iter = new CommandIterator(codes);
		while (iter.hasNext()){
			String type = iter.next2CharAsString().toUpperCase();
			switch (type){
				case new_object:{
					NewObjectCmd cmd = new NewObjectCmd(clzFile,type);
					cmd.setOprand1(iter.next2CharAsInt());
					cmd.setOprand2(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
				case ldc:{
					LdcCmd cmd = new LdcCmd(clzFile,type);
					cmd.setOperand(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
				case bipush:{
					BiPushCmd cmd = new BiPushCmd(clzFile,type);
					cmd.setOperand(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
				case invokespecial:{
					InvokeSpecialCmd cmd = new InvokeSpecialCmd(clzFile,type);
					cmd.setOprand1(iter.next2CharAsInt());
					cmd.setOprand2(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
				case invokevirtual:{
					InvokeVirtualCmd cmd = new InvokeVirtualCmd(clzFile,type);
					cmd.setOprand1(iter.next2CharAsInt());
					cmd.setOprand2(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
				case invokestatic:{
					InvokeStaticCmd cmd = new InvokeStaticCmd(clzFile,type);
					cmd.setOprand1(iter.next2CharAsInt());
					cmd.setOprand2(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
				case putfield:{
					PutFieldCmd cmd = new PutFieldCmd(clzFile,type);
					cmd.setOprand1(iter.next2CharAsInt());
					cmd.setOprand2(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
				case getfield:{
					GetFieldCmd cmd = new GetFieldCmd(clzFile,type);
					cmd.setOprand1(iter.next2CharAsInt());
					cmd.setOprand2(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
				case getstatic:{
					GetStaticFieldCmd cmd = new GetStaticFieldCmd(clzFile,type);
					cmd.setOprand1(iter.next2CharAsInt());
					cmd.setOprand2(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
                case iinc:{
                    IncrementCmd cmd = new IncrementCmd(clzFile,type);
                    cmd.setOprand1(iter.next2CharAsInt());
                    cmd.setOprand2(iter.next2CharAsInt());
                    commands.add(cmd);
                    break;
                }
				// 如何处理没有类定义的指令？
                case iadd:
				case voidreturn:
				case ireturn:
				case dup:
				case astore_1:
                case aconst_null:
                case iconst_m1:
				case iconst_0:
				case iconst_1:
				case iconst_2:
				case iconst_3:
				case iconst_4:
				case iconst_5:
				case aload_0:
				case aload_1:
				case aload_2:
				case istore_1:
                case istore_2:
				case iload_1:
				case iload_2:
				case iload_3:{
					NoOperandCmd cmd = new NoOperandCmd(clzFile,type);
					commands.add(cmd);
					break;
				}
				case goto_no_condition:
				case if_icmple:
				case if_icmp_ge:{
					ComparisonCmd cmd = new ComparisonCmd(clzFile,type);
					cmd.setOprand1(iter.next2CharAsInt());
					cmd.setOprand2(iter.next2CharAsInt());
					commands.add(cmd);
					break;
				}
				default:{
					throw new RuntimeException("Command has not been implemented:"+type);
				}
			}

		}
		calcuateOffset(commands);
		ByteCodeCommand[] byteCodeCommands = new ByteCodeCommand[commands.size()];
		return commands.toArray(byteCodeCommands);
	}

	private static void calcuateOffset(List<ByteCodeCommand> cmds) {

		int offset = 0;
		for (ByteCodeCommand cmd : cmds) {
			cmd.setOffset(offset);
			offset += cmd.getLength();
		}

	}

	private static class CommandIterator {
		String codes = null;
		int pos = 0;

		CommandIterator(String codes) {
			this.codes = codes;
		}

		public boolean hasNext() {
			return pos < this.codes.length();
		}

		public String next2CharAsString() {
			String result = codes.substring(pos, pos + 2);
			pos += 2;
			return result;
		}

		public int next2CharAsInt() {
			String s = this.next2CharAsString();
			return Integer.valueOf(s, 16).intValue();
		}

	}
}
