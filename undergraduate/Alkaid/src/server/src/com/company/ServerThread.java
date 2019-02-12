package com.company;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

/**
 * Created by asus on 2016/9/8.
 */
class ServerThread implements Runnable {

    Socket socket = null;
    public ServerThread(Socket socket){
        System.out.println("Create a new ServerThread...");
        this.socket = socket;
        man[0][0]="1";man[0][1]="5";man[0][2]="608";man[0][3]="288";man[0][4]="0";
        man[1][0]="2";man[1][1]="5";man[1][2]="448";man[1][3]="288";man[1][4]="0";
    }

    static String[][] man=new String[2][5];

    @Override
    public void run() {
        InputStream in = null;
        OutputStream out = null;
        String msg;
        try {
            in = socket.getInputStream();
            out  = socket.getOutputStream();
            //使用循环的方式，不停的与客户端交互会话
            doWrite("1#5#608#288#0#2#5#448#288#0#",out);
            while(true){
//                try {
//                    Thread.sleep(100);
//                } catch (InterruptedException e) {
//                    e.printStackTrace();
//                }


                //处理客户端发来的数据
                msg=doRead(in);
                String[] StrArray = msg.split("#");
                if(StrArray[0].equals("sx")){
                    for(int k=0;k<2;k++){
                        if(StrArray[1].equals(man[k][0])){
                            man[k][1]=StrArray[2];
                            man[k][2]=StrArray[3];
                            man[k][3]=StrArray[4];
                            man[k][4]=StrArray[5];
                        }
                    }
                }
                System.out.println("send Message to client.");
                //发送数据回客户端
                msg="";
                for(int k=0;k<2;k++,msg+="#") {
                    msg=msg+man[k][0]+"#"+man[k][1]+"#"+man[k][2]+"#"+man[k][3]+"#"+man[k][4];
                }
                doWrite(msg,out);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
        finally{
            try {
                in.close();
                out.close();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    /**
     * 读取数据
     * @param in
     * @return
     */
    public static String doRead(InputStream in){
        //引用关系，不要在此处关闭流
        byte[] bytes = new byte[1024];
        try {
            in.read(bytes);
            System.out.println("line:"+new String(bytes).trim());
        } catch (IOException e) {
            e.printStackTrace();
        }
        String msg=new String(bytes).trim();
        return msg;
    }

    /**
     * 写入数据
     * @param out
     * @return
     */
    public boolean doWrite(String msg,OutputStream out){
        //引用关系，不要在此处关闭流
        try {
            out.write(msg.getBytes());
            out.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }
}