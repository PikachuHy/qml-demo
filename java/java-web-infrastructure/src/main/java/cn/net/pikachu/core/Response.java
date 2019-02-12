package cn.net.pikachu.core;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

/**
 * 所有前后端分类的请求，返回这个包装类
 */
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class Response<T> extends BaseObject{
    /**
     * 自定义响应码
     */
    private Integer code;
    /**
     * 响应数据
     */
    private T data;
    /**
     * 正常情况下，对没有响应数据的情况一个解释
     * 出错情况下，前端显示文案
     */
    private String msg;

    private static final Integer OK = 200;
    private static final Integer BAD_REQUEST = 400;
    private static final Integer  INTERNAL_SERVER_ERROR = 500;

    public static Response success(){
        return new Response(OK, null, null);
    }
    public static Response success(Object data){
        return new Response(OK, data, null);
    }

    public static Response success(Object data, String msg){
        return new Response(OK, data, msg);
    }

    public static Response fail(String msg) {
        return new Response(BAD_REQUEST, null, msg);
    }

    public static Response failForInternalServerError(String msg) {
        return new Response(INTERNAL_SERVER_ERROR, null, msg);
    }

    public static Response fail(Object data, String msg){
        return new Response(BAD_REQUEST, data, msg);
    }
}
