package com.ziroby.dmassist.server.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.model.EnhancedEntity;
import com.ziroby.dmassist.model.EnhancedEntityList;
import lombok.Getter;
import lombok.Setter;
import org.springframework.beans.BeanUtils;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;


@Setter
@Getter
public class Battle {
    private final Integer initCount;
    private final int numRounds;
    private final String time;
    private final int id;
    private Collection<JsonEntity> entities;

    private final static AtomicInteger nextId = new AtomicInteger();

    public Battle(EnhancedEntityList entityList) {
        this.id = nextId.addAndGet(1);
        this.setEntities(entityList.getEnhancedEntities().stream()
                .map(JsonEntity::new)
                .collect(Collectors.toList()));
        initCount = entityList.getInitCount();
        numRounds = entityList.getNumRounds();
        time = entityList.formatRoundsAsTime();

        if (initCount != null) {
            this.entities.forEach(
                    entity -> {
                        if (entity.getInitRoll() == initCount) {
                            entity.setMyTurn(true);
                        }
                    }
            );
        }
    }

}
