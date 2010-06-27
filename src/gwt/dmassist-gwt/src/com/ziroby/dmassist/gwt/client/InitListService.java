package com.ziroby.dmassist.gwt.client;

import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

@RemoteServiceRelativePath("initList")
public interface InitListService extends RemoteService
{
    public void setInitCount(Integer count);
    public Integer getInitCount();
}
