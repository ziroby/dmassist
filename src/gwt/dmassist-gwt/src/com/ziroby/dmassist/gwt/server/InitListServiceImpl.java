package com.ziroby.dmassist.gwt.server;

import com.google.gwt.user.server.rpc.RemoteServiceServlet;
import com.ziroby.dmassist.gwt.client.InitListService;

public class InitListServiceImpl extends RemoteServiceServlet implements
        InitListService
{
    private Integer initCount;

    public void setInitCount(Integer count) {
        initCount = count;
    }

    public Integer getInitCount() {
        return initCount;
    }

}
