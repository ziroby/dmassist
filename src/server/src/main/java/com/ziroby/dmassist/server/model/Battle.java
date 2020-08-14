package com.ziroby.dmassist.server.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.ziroby.dmassist.model.EnhancedEntityList;
import lombok.Getter;
import lombok.Setter;

import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;


@Setter
@Getter
public class Battle {
    private final int id;

    @JsonIgnore
    private final AtomicInteger nextId = new AtomicInteger();

    @JsonIgnore
    private final EnhancedEntityList entityList;

    @JsonProperty("entities")
    public List<JsonEntity> getEntitiesAsList() {
        return this.entityList.getEnhancedEntities().stream()
                .map(JsonEntity::new)
                .collect(Collectors.toList());
    }

    public Battle(EnhancedEntityList entityList) {
        this.id = nextId.addAndGet(1);
        this.entityList = entityList;
    }

    public Integer getInitCount() {
        return entityList.getInitCount();
    }
    public int getNumRounds() {
        return entityList.getNumRounds();
    }

    public String getTime() {
        return entityList.formatRoundsAsTime();
    }

    public void addSampleData() {
        entityList.addSampleData();
    }

    public void gotoNextInitCount() {
        entityList.gotoNextInitCount();
    }

    public void resetNumRounds() {
        entityList.getNumRounds();
    }
}
