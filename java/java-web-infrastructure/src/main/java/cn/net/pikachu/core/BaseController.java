package cn.net.pikachu.core;

/**
 * 所有的Controller基于此
 */
public abstract class BaseController {
    protected Response success(){
        return Response.success();
    }
    protected Response success(String msg){
        return Response.success(null, msg);
    }
    protected Response success(Object data) {
        return Response.success(data);
    }
    protected Response success(Object data, String msg) {
        return Response.success(data, msg);
    }
    protected Response fail(String msg) {
        return Response.fail(msg);
    }
    protected Response failForServer(String msg) {
        return Response.failForInternalServerError(msg);
    }
}
