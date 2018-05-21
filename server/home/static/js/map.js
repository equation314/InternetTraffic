var infoWindow,
  map,
  navi,
  zooms = [8, 19],
  center = { lng: 116.442263, lat: 39.835354 },
  PathSimplifier;

src = [117.08276, 39.95343];
dst = [117.08538, 39.95314];
cars = [
  [117.08422, 39.95326],
  [117.08195, 39.95647],
  [117.08195, 39.95647],
  [117.08499, 39.95949],
  [117.08364, 39.94695]
];
otherPassengers = [
  [117.08538, 39.95314],
  [117.01075, 40.03353],
  [116.96512, 39.99651],
  [116.82978, 39.94889]
];
path = [cars[2], src].concat(otherPassengers);

carMarks = [];
passengerMasks = [];
otherMarks = [];

function getCarSpeed(zoom) {
  return 10000 / Math.pow(2, (zoom - 8) / 1.5);
}

function markIcon(color) {
  return new AMap.Icon({
    size: new AMap.Size(24, 28),
    image: "static/img/marks.png",
    imageSize: new AMap.Size(480, 30),
    imageOffset: new AMap.Pixel(-color * 24, 0)
  });
}

function newMark(position, color, label) {
  return new AMap.Marker({
    map: map,
    position: position,
    topWhenClick: true,
    clickable: true,
    offset: new AMap.Pixel(-12, -27),
    icon: color !== undefined ? markIcon(color) : null,
    label:
      label !== undefined
        ? {
            content: `<div class="mark-label">${label}</div>`
          }
        : null
  });
}

function showCurrentPassenger(src, dst) {
  srcMark = newMark(src, 2, "起");
  dstMark = newMark(dst, 0, "终");
  passengerMasks = [srcMark, dstMark];
}

function showCars(cars) {
  carMarks = [];
  cars.forEach((position, i) => {
    mark = newMark(position);
    mark.setOffset(new AMap.Pixel(-8, -16));
    mark.setIcon(
      new AMap.Icon({
        size: new AMap.Size(16, 32),
        image: "static/img/car.png",
        imageSize: new AMap.Size(16, 32)
      })
    );
    carMarks.push(mark);
  });
}

function showPassengers(pass) {
  otherMarks = [];
  pass.forEach((position, i) => {
    mark = newMark(position, 3, "客");
    otherMarks.push(mark);
  });
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

function showPath() {
  if (!PathSimplifier) return;

  var pathSimplifierIns = new PathSimplifier({
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
          strokeStyle: "#cc3f58"
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

  pathSimplifierIns.setData([
    {
      path: path
    }
  ]);

  navi = pathSimplifierIns.createPathNavigator(0, {
    loop: true,
    speed: getCarSpeed(map.getZoom())
  });

  navi.start();
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
  AMapUI.load(["ui/misc/PathSimplifier"], function(ps) {
    PathSimplifier = ps;
    showPath();
  });

  initMap();

  showCars(cars);

  showPassengers(otherPassengers);

  showCurrentPassenger(src, dst);

  map.setFitView();

  getNearestNode(src, data => {
    console.log(data);
  });
  getSolution(2334, 2334, data => {
    console.log(data);
  });
});
