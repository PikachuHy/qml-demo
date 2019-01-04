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
    private static long NS_2_MS = 1_000_000;
    private static long MS_2_S = 1_000;
    private static long S_2_M = 60;
    protected Object process(ProceedingJoinPoint pjp, StringBuilder sb) throws Throwable {
        long beginTime = System.nanoTime();
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
            if (it == null) {
                return "null object";
            }
            return it.toString();
        }).collect(Collectors.toList());
        //根据连接点类的名字获取指定类
        Class targetClass = Class.forName(targetName);
        //获取类里面的方法
        Method[] methods = targetClass.getMethods();
        Object object = pjp.proceed();
        long endTime = System.nanoTime();
        long duration = endTime - beginTime;
        sb.append(targetClass.getCanonicalName())
                .append(".")
                .append(methodName)
                .append("(")
                .append(StringUtils.join(list, ", "))
                .append(")")
                .append(object)
                .append(" 耗时: ")
                .append(calculateTime(duration));
        return object;
    }
    private String calculateTime(long ns) {
        if (ns < NS_2_MS) {
            return ns + " 纳秒";
        }
        long ms = ns / NS_2_MS;
        ns = ns % NS_2_MS;
        if (ms < MS_2_S) {
            return ms + " 毫秒 " + ns + " 纳秒";
        }
        long s = ms / MS_2_S;
        ms = ms % MS_2_S;
        if (s < S_2_M) {
            return s + " 秒 " + ms + " 毫秒 " + ns + " 纳秒";
        }
        long m = s / S_2_M;
        s = s % S_2_M;
        return m + " 分 " + s + " 秒 " + ms + " 毫秒 " + ns + " 纳秒";
    }
}
