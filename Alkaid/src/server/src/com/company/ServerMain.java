package com.company;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerMain {
    /**
     * @param args
     */
    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        System.out.println("ServerSocket Begin........");
        int num = 0;
        try {
            serverSocket = new ServerSocket(8888);
            //使用循环方式一直等待客户端的连接
            while(true){
                num ++;
                Socket accept = serverSocket.accept();
                //启动一个新的线程，接管与当前客户端的交互会话
                new Thread(new ServerThread(accept),"Client "+num).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        finally{
            try {
                serverSocket.close();
                System.out.println("---->  serverSocket closed.");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}