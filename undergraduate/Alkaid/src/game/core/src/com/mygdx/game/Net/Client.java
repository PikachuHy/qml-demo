package com.mygdx.game.Net;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

/**
 * Created by asus on 2016/9/8.
 */
public class Client {

    Socket socket = null;
    OutputStream out = null;
    InputStream in = null;

    public Client(Socket socket, OutputStream out, InputStream in){
        this.socket = socket;
        this.out = out;
        this.in = in;
    }
//    @Override
//    public void run() {
//        OutputStream out = null;
//        InputStream in = null;
//        System.out.println("Begin to Chat to server...");
//        try {
//            out = socket.getOutputStream();
//            in = socket.getInputStream();
//            //循环发送与服务端不停的交互数据
//            while(true){
//                try {
//                    Thread.sleep(1000);
//                } catch (InterruptedException e) {
//                    e.printStackTrace();
//                }
//                doWrite(out);
//                System.out.println("begin read message from server.");
//                doRead(in);
//            }
//
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        finally{
//            try {
//                in.close();
//                out.close();
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }
//    }

    /**
     * 读取服务端数据
     * @param in
     * @return
     */
    public static String doRead(InputStream in){
        //引用关系，不要在此处关闭流
        byte[] bytes = new byte[1024];
        try {
            in.read(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
        String msg=new String(bytes).trim();
        return msg;
    }

    /**
     * 发送数据到服务端
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