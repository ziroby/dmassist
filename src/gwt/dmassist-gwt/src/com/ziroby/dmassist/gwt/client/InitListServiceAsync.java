package com.ziroby.dmassist.gwt.client;

import com.google.gwt.user.client.rpc.AsyncCallback;

public interface InitListServiceAsync
{

    void setInitCount(Integer count, AsyncCallback<Void> callback);

    void getInitCount(AsyncCallback<Integer> callback);

}
