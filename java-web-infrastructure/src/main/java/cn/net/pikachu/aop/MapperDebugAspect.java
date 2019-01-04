package cn.net.pikachu.aop;

import lombok.extern.slf4j.Slf4j;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;

/**
 * Mapper调试用切面，可以快速了解输入输出是
 */
@Aspect
@Component
@Slf4j
public class MapperDebugAspect extends BaseAspect {
    @Pointcut("execution(* com.sumixer.ys.manager.mapper.*.*(..))")
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
