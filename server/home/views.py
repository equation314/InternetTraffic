from django.shortcuts import render
from django.http import HttpResponse
import json
import home.api as api


def index(request):
    return render(request, 'index.html')
    # return HttpResponse(index_temp.render())


def nearestNode(request):
    form_data = request.GET
    if request.method == 'GET' and 'location' in form_data:
        try:
            lon, lat = map(float, form_data['location'].split(','))
            id, location = api.getNearestNode(lon, lat)

            return HttpResponse(json.dumps({
                'succes': True,
                'location': location,
                'id': id
            }))
        except Exception as e:
            print(e)
            return HttpResponse('{}')
    return HttpResponse('{}')


def query(request):
    form_data = request.GET
    if request.method == 'GET' and 'srcId' in form_data and 'dstId' in form_data:
        try:
            srcId = form_data['srcId']
            dstId = form_data['dstId']
            solutions = api.query(srcId, dstId)

            return HttpResponse(json.dumps({
                'succes': True,
                'cars': solutions,
            }))
        except Exception as e:
            print(e)
            return HttpResponse('{}')
    return HttpResponse('{}')
