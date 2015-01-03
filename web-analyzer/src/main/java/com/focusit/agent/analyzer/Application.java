package com.focusit.agent.analyzer;

import com.focusit.agent.analyzer.data.netty.jvm.JvmDataImport;
import com.focusit.agent.analyzer.data.netty.jvm.NettyJvmData;
import com.focusit.agent.analyzer.data.netty.methodmap.MethodMapImport;
import com.focusit.agent.analyzer.data.netty.methodmap.NettyMethodMapData;
import com.focusit.agent.analyzer.data.netty.session.NettySessionStart;
import com.focusit.agent.analyzer.data.netty.statistics.NettyStatisticsData;
import com.focusit.agent.analyzer.data.netty.statistics.StatisticsImport;
import com.focusit.agent.metrics.dump.netty.NettyThreadFactory;
import com.mongodb.DB;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.context.web.SpringBootServletInitializer;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.ComponentScan;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by Denis V. Kirpichenkov on 14.12.14.
 */
@SpringBootApplication
@ComponentScan(basePackages = {"com.focusit"})
public class Application extends SpringBootServletInitializer {

	public static void main(String[] args) throws Exception {
		ApplicationContext ctx = SpringApplication.run(Application.class, args);

		ExecutorService service = Executors.newFixedThreadPool(4, new NettyThreadFactory("NettyExecutorService"));
		MethodMapImport methodMapImport = new MethodMapImport(ctx.getBean(DB.class));
		JvmDataImport jvmDataImport = new JvmDataImport(ctx.getBean(DB.class));
		StatisticsImport statisticsImport = new StatisticsImport(ctx.getBean(DB.class));

		service.submit(new NettySessionStart(methodMapImport, jvmDataImport, statisticsImport));

		service.submit(new NettyMethodMapData(methodMapImport));
		service.submit(new NettyJvmData(jvmDataImport));
		service.submit(new NettyStatisticsData(statisticsImport));
	}
}
