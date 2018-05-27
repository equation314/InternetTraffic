var infoWindow,
  map,
  navi,
  zooms = [10, 19],
  center = { lng: 116.397428, lat: 39.90923 },
  pathSimplifierIns,
  infoWindow;

var src = null,
  dst = null,
  cars = [];

var srcMark = null,
  dstMark = null,
  carMarks = [],
  otherMarks = [],
  currentCarMark = null;

var carIcon = new AMap.Icon({
  size: new AMap.Size(16, 32),
  image: "static/img/car.png",
  imageSize: new AMap.Size(16, 32)
});
var carActivedIcon = new AMap.Icon({
  size: new AMap.Size(16, 32),
  image: "static/img/car_actived.png",
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

function showCars(cars) {
  clearMarks();

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

      AMap.event.addListener(carMarks[i], "click", event => {
        if (currentCarMark) currentCarMark.setIcon(carIcon);
        currentCarMark = carMarks[i];
        carMarks[i].setIcon(carActivedIcon);
        showCarPath(i);

        infoWindow.setContent(event.target.content);
        infoWindow.open(map, event.target.getPosition());
      });
    }

    carMarks[i].content =
      `<div>车辆距您 ${car.dis.toFixed(2)} km</div>` +
      `<div>您的行程总距离 ${car.total_dis.toFixed(2)} km</div>` +
      `<div>您需绕路 ${car.detour_dis2.toFixed(2)} km</div>` +
      `<div>车上乘客需绕路 ${car.detour_dis1.toFixed(2)} km</div>`;

    carMarks[i].setAngle(car.angle);
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

function showCarPath(index) {
  if (!pathSimplifierIns) return;

  let car = cars[index];
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

function clearMarks(clearSrcDst = false) {
  if (currentCarMark) {
    currentCarMark.setIcon(carIcon);
    currentCarMark = null;
  }
  if (infoWindow) {
    infoWindow.close();
  }
  pathSimplifierIns && pathSimplifierIns.setData(null);
  otherMarks.forEach(mark => mark.hide());
  carMarks.forEach(mark => mark.hide());
  if (clearSrcDst) {
    src = dst = null;
    srcMark && srcMark.hide();
    dstMark && dstMark.hide();
    $("#btn-action").text("选择起点");
    $("#btn-action").prop("disabled", false);
  }
}

function onClickActionButton() {
  $("#btn-action").prop("disabled", true);
  if (src && dst) {
    $("#btn-clear").prop("disabled", true);
    $("#btn-action").text("查询中...");
    getSolution(src.id, dst.id, data => {
      cars = data.cars;
      $("#btn-clear").prop("disabled", false);
      $("#btn-action").text("查询");
      if (!cars.length) {
        alert("没有合适的出租车！");
        return;
      }
      showCars(cars);
      map.setFitView();
    });
  }
}

function onClickMap(position) {
  if (!$("#btn-action").prop("disabled")) return;
  if (!src) {
    getNearestNode(position, data => {
      src = data;
      if (!srcMark) srcMark = newMark(src.location, 2, "起");
      srcMark.setPosition(src.location);
      srcMark.show();
      $("#btn-action").prop("disabled", false);
      $("#btn-action").text("选择终点");
    });
  } else if (!dst) {
    getNearestNode(position, data => {
      dst = data;
      if (!dstMark) dstMark = newMark(dst.location, 0, "终");
      dstMark.setPosition(dst.location);
      dstMark.show();
      $("#btn-action").prop("disabled", false);
      $("#btn-action").text("查询");
    });
  }
}

function initMap() {
  map = new AMap.Map("container", {
    center: new AMap.LngLat(center.lng, center.lat),
    resizeEnable: true,
    zooms: zooms
  });

  infoWindow = new AMap.InfoWindow({
    offset: new AMap.Pixel(0, -10)
  });

  map.on("complete", function() {
    map.plugin(["AMap.ToolBar", "AMap.Scale"], function() {
      map.addControl(new AMap.ToolBar());
      map.addControl(new AMap.Scale());
    });
  });
  map.on("click", function(e) {
    onClickMap([e.lnglat.getLng(), e.lnglat.getLat()]);
  });

  AMap.event.addListener(map, "zoomend", function() {
    if (navi) navi.setSpeed(getCarSpeed(map.getZoom()));
  });
  document
    .getElementById("btn-action")
    .addEventListener("click", onClickActionButton, false);
  document
    .getElementById("btn-clear")
    .addEventListener("click", () => clearMarks(true), false);
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
    autoSetFitView: false,
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
          strokeStyle: "#ffaa00"
        },
        content: PathSimplifier.Render.Canvas.getImageContent(
          "static/img/car_actived.png",
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
  });
});
