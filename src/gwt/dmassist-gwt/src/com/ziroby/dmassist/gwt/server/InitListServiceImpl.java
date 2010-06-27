package com.ziroby.dmassist.gwt.server;

import com.google.gwt.user.server.rpc.RemoteServiceServlet;
import com.ziroby.dmassist.gwt.client.InitListService;

public class InitListServiceImpl extends RemoteServiceServlet implements
        InitListService
{
    private Integer initCount;
    private int numRounds;

    public void setInitCount(Integer count) {
        initCount = count;
    }

    public Integer getInitCount() {
        return initCount;
    }

    public Integer getNumRounds() {
        return numRounds;
    }

    public void setNumRounds(Integer numRounds) {
        this.numRounds = numRounds;
    }
}
