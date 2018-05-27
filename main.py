from itrafficpy import InternetTraffic

if __name__ == '__main__':
    engine = InternetTraffic('data/')

    srcLon, srcLat = 117.08276, 39.95343
    dstLon, dstLat = 117.08538, 39.95314
    src = engine.get_nearest_node(srcLon, srcLat)
    dst = engine.get_nearest_node(dstLon, dstLat)
    res = engine.query(src[0], dst[0])

    for sol in res.result:
        sol.print()
