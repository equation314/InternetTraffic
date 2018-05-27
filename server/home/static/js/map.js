var infoWindow,
  map,
  navi,
  zooms = [8, 19],
  center = { lng: 116.442263, lat: 39.835354 },
  pathSimplifierIns;

var src = null,
  dst = null,
  cars = [];

var srcMark = null,
  dstMark = null,
  carMarks = [],
  otherMarks = [];

var carIcon = new AMap.Icon({
  size: new AMap.Size(16, 32),
  image: "static/img/car.png",
  imageSize: new AMap.Size(16, 32)
});

function getCarSpeed(zoom) {
  return 10000 / Math.pow(2, (zoom - 8) / 1.5);
}

function isSameNode(a, b) {
  return a.location[0] === b.location[0] && a.location[1] === b.location[1];
}

function markIcon(color) {
  return new AMap.Icon({
    size: new AMap.Size(24, 28),
    image: "static/img/marks.png",
    imageSize: new AMap.Size(480, 30),
    imageOffset: new AMap.Pixel(-color * 24, 0)
  });
}

function newMark(position, icon, label) {
  return new AMap.Marker({
    map: map,
    position: position,
    topWhenClick: true,
    clickable: true,
    offset: new AMap.Pixel(-12, -27),
    icon: typeof icon == "number" ? markIcon(icon) : icon,
    label:
      label !== undefined
        ? {
            content: `<div class="mark-label">${label}</div>`
          }
        : null
  });
}

function showCurrentPassenger(src, dst) {
  if (!srcMark) srcMark = newMark(src, 2, "起");
  else srcMark.setPosition(src);

  if (!dstMark) dstMark = newMark(dst, 0, "终");
  else dstMark.setPosition(src);
}

function showCars(cars) {
  carMarks.forEach(mark => mark.hide());
  cars.forEach((car, i) => {
    for (let j = 0; j < i; j++)
      if (isSameNode(cars[j], car)) {
        cars[i].location[0] += (Math.random() - 0.5) / 5000;
        cars[i].location[1] += (Math.random() - 0.5) / 5000;
      }
  });
  cars.forEach((car, i) => {
    if (!carMarks[i]) {
      carMarks[i] = newMark(car.location, carIcon);
      carMarks[i].setOffset(new AMap.Pixel(-8, -16));
      carMarks[i].setzIndex(99);
      carMarks[i].setAngle(car.angle);

      AMap.event.addListener(carMarks[i], "click", event => {
        showCarPath(cars[i]);
      });
    }
    carMarks[i].setPosition(car.location);
    carMarks[i].show();
  });
}

function showPassengers(pass) {
  otherMarks.forEach(mark => mark.hide());
  pass.forEach((position, i) => {
    if (!otherMarks[i]) {
      otherMarks[i] = newMark(position, 3, "客");
    }
    otherMarks[i].setPosition(position);
    otherMarks[i].show();
  });
}

function showCarPath(car) {
  if (!pathSimplifierIns) return;

  showPassengers(car.passengers);

  pathSimplifierIns.setData([
    {
      path: car.path
    }
  ]);

  navi = pathSimplifierIns.createPathNavigator(0, {
    loop: true,
    speed: getCarSpeed(map.getZoom())
  });

  navi.start();
}

function initMap() {
  map = new AMap.Map("mapContainer", {
    center: new AMap.LngLat(center.lng, center.lat),
    resizeEnable: true,
    zooms: zooms
  });

  map.on("complete", function() {
    map.plugin(["AMap.ToolBar", "AMap.Scale"], function() {
      map.addControl(new AMap.ToolBar());
      map.addControl(new AMap.Scale());
    });
  });

  AMap.event.addListener(map, "zoomend", function() {
    if (navi) navi.setSpeed(getCarSpeed(map.getZoom()));
  });
}

function initPathSimplifier(PathSimplifier) {
  pathSimplifierIns = new PathSimplifier({
    zIndex: 100,
    map: map,
    getPath: function(pathData, pathIndex) {
      return pathData.path;
    },
    getHoverTitle: function(pathData, pathIndex, pointIndex) {
      return null;
    },
    clickToSelectPath: false,
    renderOptions: {
      pathLineStyle: {
        strokeStyle: "#22aa99",
        lineWidth: 6,
        dirArrowStyle: true
      },
      pathLineHoverStyle: null,
      pathNavigatorStyle: {
        width: 16,
        height: 32,
        strokeStyle: null,
        fillStyle: null,
        pathLinePassedStyle: {
          strokeStyle: "#ff6600"
        },
        content: PathSimplifier.Render.Canvas.getImageContent(
          "static/img/car.png",
          function onload() {
            pathSimplifierIns.renderLater();
          }
        )
      }
    }
  });
}

function getNearestNode(position, callback) {
  $.get(
    "nearestnode",
    {
      location: position.join(",")
    },
    callback,
    "json"
  );
}

function getSolution(srcId, dstId, callback) {
  $.get(
    "query",
    {
      srcId: srcId,
      dstId: dstId
    },
    callback,
    "json"
  );
}

$(document).ready(() => {
  initMap();

  AMapUI.load(["ui/misc/PathSimplifier"], function(PathSimplifier) {
    initPathSimplifier(PathSimplifier);

    getNearestNode([117.08276, 39.95343], data => {
      src = data;
      getNearestNode([117.08538, 39.95314], data => {
        dst = data;
        showCurrentPassenger(src.location, dst.location);
        getSolution(src.id, dst.id, data => {
          cars = data.cars;
          showCars(cars);
          map.setFitView();
        });
      });
    });
  });
});
