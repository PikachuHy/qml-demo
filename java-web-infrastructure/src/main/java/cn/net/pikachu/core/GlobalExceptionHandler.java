package cn.net.pikachu.core;

import lombok.extern.slf4j.Slf4j;
import org.springframework.http.converter.HttpMessageNotReadableException;
import org.springframework.validation.BindingResult;
import org.springframework.validation.FieldError;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestController;

import java.sql.SQLException;
import java.util.List;

@ControllerAdvice
@Slf4j
@RestController
public class GlobalExceptionHandler extends BaseController{
    private static final String INTERNAL_SERVER_ERROR_MSG
            = "非常抱歉，服务器正在维护，请及时联系技术支持人员，我们会尽快恢复，谢谢。";
    @ExceptionHandler(Exception.class)
    public Response exceptionHandler(Exception ex){
        String msg = ex.getMessage();
        ex.printStackTrace();
        logger.error("ex: {}", msg);
        return fail(msg);
    }

    /**
     * JSON反序列化失败
     * @param ex
     * @return
     */
    @ExceptionHandler(HttpMessageNotReadableException.class)
    public Response httpMessageNotReadableExceptionHandler(Exception ex){
        String msg = ex.getMessage();
        ex.printStackTrace();
        logger.error("ex: {}", msg);
        return fail("对不起，请求参数有误，请调整后重新请求");
    }
    /**
     * JSON反序列化失败
     * @param ex
     * @return
     */
    @ExceptionHandler(NullPointerException.class)
    public Response nullPointerExceptionHandler(Exception ex){
        String msg = ex.getMessage();
        ex.printStackTrace();
        logger.error("ex: {}", msg);
        return failForServer(INTERNAL_SERVER_ERROR_MSG);
    }
    /**
     * 严重警告，生产环境不许出现这样的错误，如果出现这样的错误，必定是有严重的错误
     * 捕获不到这个异常？
     * @param ex
     * @return
     */
    @ExceptionHandler(SQLException.class)
    public Response sqlExceptionHandler(Exception ex){
        String msg = ex.getMessage();
        ex.printStackTrace();
        logger.error("ex: {}", msg);
        return failForServer(INTERNAL_SERVER_ERROR_MSG);
    }
    /**
     * 处理实体字段校验不通过异常
     * @param ex
     * @return
     */
    @ExceptionHandler(MethodArgumentNotValidException.class)
    public Response validationError(MethodArgumentNotValidException ex) {
        logger.error("raised MethodArgumentNotValidException : {} " , ex.getMessage());
        ex.printStackTrace();
        BindingResult result = ex.getBindingResult();
        final List<FieldError> fieldErrors = result.getFieldErrors();
        StringBuilder builder = new StringBuilder();

        for (FieldError error : fieldErrors) {
            builder.append(error.getDefaultMessage()).append("\n");
        }
        return fail(builder.toString());
    }
}
