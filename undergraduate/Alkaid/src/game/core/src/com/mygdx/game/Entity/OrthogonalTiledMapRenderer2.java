package com.mygdx.game;

/**
 * Created by Spica on 2016/9/5.
 */
import static com.badlogic.gdx.graphics.g2d.Batch.C1;
import static com.badlogic.gdx.graphics.g2d.Batch.C2;
import static com.badlogic.gdx.graphics.g2d.Batch.C3;
import static com.badlogic.gdx.graphics.g2d.Batch.C4;
import static com.badlogic.gdx.graphics.g2d.Batch.U1;
import static com.badlogic.gdx.graphics.g2d.Batch.U2;
import static com.badlogic.gdx.graphics.g2d.Batch.U3;
import static com.badlogic.gdx.graphics.g2d.Batch.U4;
import static com.badlogic.gdx.graphics.g2d.Batch.V1;
import static com.badlogic.gdx.graphics.g2d.Batch.V2;
import static com.badlogic.gdx.graphics.g2d.Batch.V3;
import static com.badlogic.gdx.graphics.g2d.Batch.V4;
import static com.badlogic.gdx.graphics.g2d.Batch.X1;
import static com.badlogic.gdx.graphics.g2d.Batch.X2;
import static com.badlogic.gdx.graphics.g2d.Batch.X3;
import static com.badlogic.gdx.graphics.g2d.Batch.X4;
import static com.badlogic.gdx.graphics.g2d.Batch.Y1;
import static com.badlogic.gdx.graphics.g2d.Batch.Y2;
import static com.badlogic.gdx.graphics.g2d.Batch.Y3;
import static com.badlogic.gdx.graphics.g2d.Batch.Y4;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.SpriteCache;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.maps.MapLayer;
import com.badlogic.gdx.maps.MapLayers;
import com.badlogic.gdx.maps.MapObject;
import com.badlogic.gdx.maps.tiled.*;
import com.badlogic.gdx.maps.tiled.TiledMapTileLayer.Cell;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.utils.Disposable;

public class OrthogonalTiledMapRenderer2 implements TiledMapRenderer, Disposable {

    protected TiledMap map;

    protected float unitScale;

    protected SpriteCache spriteCache;

    protected Rectangle viewBounds;

    protected float[] vertices = new float[20];

    protected boolean recache;

    protected Rectangle cacheBounds;

    protected float overCache = 0.50f;

    protected boolean cached = false;
    protected int count = 0;

    protected float minX = +Float.MAX_VALUE;
    protected float maxX = -Float.MAX_VALUE;
    protected float minY = +Float.MAX_VALUE;
    protected float maxY = -Float.MAX_VALUE;

    protected boolean canCacheMoreN;
    protected boolean canCacheMoreE;
    protected boolean canCacheMoreW;
    protected boolean canCacheMoreS;

    protected boolean hitCache;

    @Override
    public void renderImageLayer(TiledMapImageLayer layer){

    }
    @Override
    public void renderObjects (MapLayer layer){

    }

    public OrthogonalTiledMapRenderer2(TiledMap map) {
        this.map = map;
        this.unitScale = 1;
        this.spriteCache = new SpriteCache(5460, true);
        this.viewBounds = new Rectangle();
        this.cacheBounds = new Rectangle();
    }

    public OrthogonalTiledMapRenderer2(TiledMap map, float unitScale) {
        this.map = map;
        this.unitScale = unitScale;
        this.viewBounds = new Rectangle();
        this.cacheBounds = new Rectangle();
        this.spriteCache = new SpriteCache(5460, true);
    }

    @Override
    public void setView(OrthographicCamera camera) {
        spriteCache.setProjectionMatrix(camera.combined);
        float width = camera.viewportWidth * camera.zoom;
        float height = camera.viewportHeight * camera.zoom;
        viewBounds.set(camera.position.x - width / 2, camera.position.y - height / 2, width, height);

        if (!recache && viewBounds.x < cacheBounds.x) {
            if (cacheBounds.x > 0) {
                recache = true;
            }
        }
        if (!recache && viewBounds.y < cacheBounds.y) {
            if (cacheBounds.y > 0) {
                recache = true;
            }
        }
        if (!recache && viewBounds.x + viewBounds.width > cacheBounds.x + cacheBounds.width) {
            if (canCacheMoreE) {
                recache = true;
            }
        }
        if (!recache && viewBounds.y + viewBounds.height > cacheBounds.y + cacheBounds.height) {
            if (canCacheMoreN) {
                recache = true;
            }
        }
    }

    @Override
    public void setView (Matrix4 projection, float x, float y, float width, float height) {
        spriteCache.setProjectionMatrix(projection);
        viewBounds.set(x, y, width, height);

        if (!recache && viewBounds.x < cacheBounds.x) {
            if (canCacheMoreW) {
                recache = true;
            }
        }
        if (!recache && viewBounds.y < cacheBounds.y) {
            if (canCacheMoreS) {
                recache = true;
            }
        }
        if (!recache && viewBounds.x + viewBounds.width > cacheBounds.x + cacheBounds.width) {
            if (canCacheMoreE) {
                recache = true;
            }
        }
        if (!recache && viewBounds.y + viewBounds.height > cacheBounds.y + cacheBounds.height) {
            if (canCacheMoreN) {
                recache = true;
            }
        }
    }

    @Override
    public void render () {
        hitCache = false;
        if (recache) {
            count = 0;
            cached = false;
            recache = false;
            spriteCache.clear();
        }
        if (!cached) {
            hitCache = true;
            minX = Float.MAX_VALUE;
            maxX = Float.MIN_VALUE;
            minY = Float.MAX_VALUE;
            maxY = Float.MIN_VALUE;
            for (MapLayer layer : map.getLayers()) {
                spriteCache.beginCache();
                if (layer instanceof TiledMapTileLayer) {
                    renderTileLayer((TiledMapTileLayer) layer);
                }
                spriteCache.endCache();
            }
            cacheBounds.set(minX, minY, maxX - minX, maxY - minY);
            cached = true;
        }

        Gdx.gl.glEnable(GL20.GL_BLEND);
        Gdx.gl.glBlendFunc(GL20.GL_SRC_ALPHA, GL20.GL_ONE_MINUS_SRC_ALPHA);
        spriteCache.begin();
        MapLayers mapLayers = map.getLayers();
        for (int i = 0, j = mapLayers.getCount(); i < j; i++) {
            MapLayer layer = mapLayers.get(i);
            if (layer.isVisible()) {
                spriteCache.draw(i);
                for (MapObject object : layer.getObjects()) {
                    renderObject(object);
                }
            }

        }
        spriteCache.end();
        Gdx.gl.glDisable(GL20.GL_BLEND);
    }

    @Override
    public void render (int[] layers) {
        if (recache) {
            count = 0;
            cached = false;
            recache = false;
            spriteCache.clear();
        }
        if (!cached) {
            minX = Float.MAX_VALUE;
            maxX = Float.MIN_VALUE;
            minY = Float.MAX_VALUE;
            maxY = Float.MIN_VALUE;
            for (MapLayer layer : map.getLayers()) {
                spriteCache.beginCache();
                if (layer instanceof TiledMapTileLayer) {
                    renderTileLayer((TiledMapTileLayer) layer);
                }
                spriteCache.endCache();
            }
            cacheBounds.set(minX, minY, maxX - minX, maxY - minY);
            cached = true;
        }

        Gdx.gl.glEnable(GL20.GL_BLEND);
        Gdx.gl.glBlendFunc(GL20.GL_SRC_ALPHA, GL20.GL_ONE_MINUS_SRC_ALPHA);
        spriteCache.begin();
        MapLayers mapLayers = map.getLayers();
        for (int i : layers) {
            MapLayer layer = mapLayers.get(i);
            if (layer.isVisible()) {
                spriteCache.draw(i);
                for (MapObject object : layer.getObjects()) {
                    renderObject(object);
                }
            }

        }
        spriteCache.end();
        Gdx.gl.glDisable(GL20.GL_BLEND);
    }

    @Override
    public void renderObject (MapObject object) {

    }

    @Override
    public void renderTileLayer (TiledMapTileLayer layer) {
        final float color = Color.toFloatBits(1, 1, 1, layer.getOpacity());

        final int layerWidth = layer.getWidth();
        final int layerHeight = layer.getHeight();

        final float layerTileWidth = layer.getTileWidth() * unitScale;
        final float layerTileHeight = layer.getTileHeight() * unitScale;

        final float extraWidth = viewBounds.width * overCache;
        final float extraHeight = viewBounds.height * overCache;

        final int col1 = Math.max(0, (int) ((viewBounds.x - extraWidth) / layerTileWidth));
        final int col2 = Math.min(layerWidth, (int) ((viewBounds.x + viewBounds.width + layerTileWidth +  extraWidth) / layerTileWidth));

        final int row1 = Math.max(0, (int) ((viewBounds.y - extraHeight) / layerTileHeight));
        final int row2 = Math.min(layerHeight, (int) ((viewBounds.y + viewBounds.height + layerTileHeight + extraHeight) / layerTileHeight));


        canCacheMoreN = row2 < layerHeight;
        canCacheMoreE = col2 < layerWidth;
        canCacheMoreW = col1 > 0;
        canCacheMoreS = row1 > 0;

        for (int row = row1; row < row2; row++) {
            for (int col = col1; col < col2; col++) {
                final TiledMapTileLayer.Cell cell = layer.getCell(col, row);
                if(cell == null) continue;
                final TiledMapTile tile = cell.getTile();
                if (tile != null) {
                    count++;
                    final boolean flipX = cell.getFlipHorizontally();
                    final boolean flipY = cell.getFlipVertically();
                    final int rotations = cell.getRotation();

                    TextureRegion region = tile.getTextureRegion();

                    float x1 = col * layerTileWidth;
                    float y1 = row * layerTileHeight;
                    float x2 = x1 + region.getRegionWidth() * unitScale;
                    float y2 = y1 + region.getRegionHeight() * unitScale;

                    float u1 = region.getU();
                    float v1 = region.getV2();
                    float u2 = region.getU2();
                    float v2 = region.getV();

                    vertices[X1] = x1;
                    vertices[Y1] = y1;
                    vertices[C1] = color;
                    vertices[U1] = u1;
                    vertices[V1] = v1;

                    vertices[X2] = x1;
                    vertices[Y2] = y2;
                    vertices[C2] = color;
                    vertices[U2] = u1;
                    vertices[V2] = v2;

                    vertices[X3] = x2;
                    vertices[Y3] = y2;
                    vertices[C3] = color;
                    vertices[U3] = u2;
                    vertices[V3] = v2;

                    vertices[X4] = x2;
                    vertices[Y4] = y1;
                    vertices[C4] = color;
                    vertices[U4] = u2;
                    vertices[V4] = v1;

                    if (flipX) {
                        float temp = vertices[U1];
                        vertices[U1] = vertices[U3];
                        vertices[U3] = temp;
                        temp = vertices[U2];
                        vertices[U2] = vertices[U4];
                        vertices[U4] = temp;
                    }
                    if (flipY) {
                        float temp = vertices[V1];
                        vertices[V1] = vertices[V3];
                        vertices[V3] = temp;
                        temp = vertices[V2];
                        vertices[V2] = vertices[V4];
                        vertices[V4] = temp;
                    }
                    if (rotations != 0) {
                        switch (rotations) {
                            case Cell.ROTATE_90: {
                                float tempV = vertices[V1];
                                vertices[V1] = vertices[V2];
                                vertices[V2] = vertices[V3];
                                vertices[V3] = vertices[V4];
                                vertices[V4] = tempV;

                                float tempU = vertices[U1];
                                vertices[U1] = vertices[U2];
                                vertices[U2] = vertices[U3];
                                vertices[U3] = vertices[U4];
                                vertices[U4] = tempU;
                                break;
                            }
                            case Cell.ROTATE_180: {
                                float tempU = vertices[U1];
                                vertices[U1] = vertices[U3];
                                vertices[U3] = tempU;
                                tempU = vertices[U2];
                                vertices[U2] = vertices[U4];
                                vertices[U4] = tempU;
                                float tempV = vertices[V1];
                                vertices[V1] = vertices[V3];
                                vertices[V3] = tempV;
                                tempV = vertices[V2];
                                vertices[V2] = vertices[V4];
                                vertices[V4] = tempV;
                                break;
                            }
                            case Cell.ROTATE_270: {
                                float tempV = vertices[V1];
                                vertices[V1] = vertices[V4];
                                vertices[V4] = vertices[V3];
                                vertices[V3] = vertices[V2];
                                vertices[V2] = tempV;

                                float tempU = vertices[U1];
                                vertices[U1] = vertices[U4];
                                vertices[U4] = vertices[U3];
                                vertices[U3] = vertices[U2];
                                vertices[U2] = tempU;
                                break;
                            }
                        }
                    }
                    spriteCache.add(region.getTexture(), vertices, 0, 20);
                    minX = Math.min(x1, minX);
                    maxX = Math.max(x2, maxX);
                    minY = Math.min(y1, minY);
                    maxY = Math.max(y2, maxY);
                }
            }
        }
    }

    public void markDirty() {
        recache = true;
    }

    public boolean hitCache() {
        return hitCache;
    }

    @Override
    public void dispose () {
        spriteCache.dispose();
    }

}
