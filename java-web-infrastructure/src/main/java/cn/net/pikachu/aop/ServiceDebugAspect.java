package cn.net.pikachu.aop;

import lombok.extern.slf4j.Slf4j;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;

/**
 * Service调试用切面，可以快速了解输入输出是
 */
@Aspect
@Component
@Slf4j
public class ServiceDebugAspect extends BaseAspect{
    //    @Pointcut("@annotation(org.springframework.web.bind.annotation.RestController) || @annotation(org.springframework.stereotype.Service)")
    @Pointcut("execution(* com.sumixer.ys.api.service.*.*(..))")
    public void Pointcut() {
    }
    @Around("Pointcut()")
    public Object Around(ProceedingJoinPoint pjp) throws Throwable {
        StringBuilder sb = new StringBuilder();
        Object object = process(pjp, sb);
        logger.debug(sb.toString());
        return object;
    }
}
