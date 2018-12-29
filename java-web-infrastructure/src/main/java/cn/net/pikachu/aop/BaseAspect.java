package cn.net.pikachu.aop;

import org.apache.commons.lang3.StringUtils;
import org.aspectj.lang.ProceedingJoinPoint;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import java.lang.reflect.Method;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public abstract class BaseAspect {
    protected Object process(ProceedingJoinPoint pjp, StringBuilder sb) throws Throwable {
        //获取连接点目标类名
        String targetName = pjp.getTarget().getClass().getName();
        //获取连接点签名的方法名
        String methodName = pjp.getSignature().getName();
        //获取连接点参数
        Object[] args = pjp.getArgs();
        List<Object> list = Stream.of(args).map(it -> {
            if (it instanceof ServletRequest) {
                return "ServletRequest object";
            }
            if (it instanceof ServletResponse) {
                return "ServletResponse object";
            }
            if (it instanceof MultipartFile) {
                return "MultipartFile object";
            }
            return it.toString();
        }).collect(Collectors.toList());
        //根据连接点类的名字获取指定类
        Class targetClass = Class.forName(targetName);
        //获取类里面的方法
        Method[] methods = targetClass.getMethods();
        Object object = pjp.proceed();
        sb.append(targetClass.getCanonicalName())
                .append(".")
                .append(methodName)
                .append("(")
                .append(StringUtils.join(list,", "))
                .append(")")
                .append(object);
        return object;
    }
}
