import xml.etree.ElementTree as ET
import math

IMAGE_WIDTH = 1000
IMAGE_HEIGHT = 720 #688 sf #651 for istanbul
ID = "stanford"
IMAGE_NAME = "map-" + ID + ".png"

OSM_FILE = ID + '.osm'
OUT_NAME = 'map-' + ID + '.txt'

ON_FOOT = True

WALK_KM_PER_HOUR = 12.0
WALK_KM_PER_MIN = WALK_KM_PER_HOUR / 60

KM_PER_MILE = 1.6

def run():
	graph = {}
	graph['highwaySpeeds'] = {}

	with open('highwaySpeeds.txt') as f:
		for line in f:
			cols = line.split()
			hType = cols[0]
			speedStr = cols[1]
			if speedStr == 'None': continue
			kmPerHour = float(speedStr) * KM_PER_MILE
			graph['highwaySpeeds'][hType] = kmPerHour

	tree = ET.parse(OSM_FILE)
	root = tree.getroot()

	
	graph['nodes'] = {}
	graph['edges'] = []

	for child in root:
		if child.tag == 'bounds':
			graph['bounds'] = {}
			graph['bounds']['minLat'] = float(child.get('minlat'))
			graph['bounds']['minLon'] = float(child.get('minlon'))
			graph['bounds']['maxLat'] = float(child.get('maxlat'))
			graph['bounds']['maxLon'] = float(child.get('maxlon'))
		if child.tag == 'node':
			node = {}
			node['id'] = child.get('id')
			node['lat'] = float(child.get('lat'))
			node['lon'] = float(child.get('lon'))
			node['edges'] = []
			if inBounds(node, graph['bounds']):
				graph['nodes'][node['id']] = node
		if child.tag == 'way':
			processWay(graph, child)

		if len(graph['nodes']) % 1000 == 0:
			print len(graph['nodes'])

	makeImageGraph(graph)

	print 'nodes', len(graph['nodes'])
	print 'edges', len(graph['edges'])

def inBounds(node, bounds):
	if node['lat'] < bounds['minLat']: return False
	if node['lat'] > bounds['maxLat']: return False
	if node['lon'] < bounds['minLon']: return False
	if node['lon'] > bounds['maxLon']: return False
	return True

def getPixel(lat, lon, bounds):
	imageLonHeight = bounds['maxLon'] - bounds['minLon']
	imageLatWidth = bounds['maxLat'] - bounds['minLat']

	pointLonDiff = lon - bounds['minLon']
	pointLatDiff = lat - bounds['minLat']

	percentUp = pointLatDiff / imageLatWidth
	percentRight = pointLonDiff / imageLonHeight

	return (percentRight * IMAGE_WIDTH, IMAGE_HEIGHT - percentUp * IMAGE_HEIGHT )

def makeImageGraph(graph):
	outFile = open(OUT_NAME, 'w')
	outFile.write('FLAGS\n')
	outFile.write('largeMapDisplay=true\n')

	outFile.write('IMAGE\n')
	outFile.write(str(IMAGE_NAME) + '\n')
	outFile.write(str(IMAGE_WIDTH) + '\n')
	outFile.write(str(IMAGE_HEIGHT) + '\n')

	outFile.write('VERTICES\n')
	for nodeId in graph['nodes']:
		node = graph['nodes'][nodeId]
		if len(node['edges']) < 1: continue
		(x, y) = getPixel(node['lat'], node['lon'], graph['bounds'])
		intX = int(round(x))
		intY = int(round(y))
		if(intX <= 0): intX = 1
		if(intY <= 0): intY = 1
		if(intX >= IMAGE_WIDTH): intX = IMAGE_WIDTH - 1
		if(intY >= IMAGE_HEIGHT): intY = IMAGE_HEIGHT - 1
		outFile.write(str(nodeId) + ';' + str(intX) + ';' + str(intY) + '\n')

 	outFile.write('EDGES\n')
 	for edge in graph['edges']:
 		edgeStr = edge['start']  + ';' + edge['end'] + ';'
 		edgeStr += str(edge['weight']) + ';'
 		print edge['roadName']
 		edgeStr += str(edge['roadName'])
 		outFile.write(edgeStr + '\n')

def processWay(graph, wayNode):
	# get the type and make sure its a true "way"
	roadType = None
	for child in wayNode:
		if child.tag == 'tag' and child.get('k') == 'highway':
			roadType = child.get('v')
	if roadType == None: 
		return
	if not ON_FOOT and not roadType in graph['highwaySpeeds']:
		return

	# get the name
	roadName = ''
	for child in wayNode:
		if child.tag == 'tag' and child.get('k') == 'name':
			roadName = child.get('v')
	if ON_FOOT:
		kmPerHour = WALK_KM_PER_HOUR
	else:
		kmPerHour = graph['highwaySpeeds'][roadType]
	
	# get the waypoints
	nodeList = []
	for child in wayNode:
		if child.tag == 'nd':
			nodeId = child.get('ref')
			nodeList.append(nodeId)

	for i in range(1, len(nodeList)):
		aId = nodeList[i - 1]
		bId = nodeList[i]

		# check if the nodes were in the graph (eg they are in bounds)
		if not aId in graph['nodes']: continue
		if not bId in graph['nodes']: continue

		aNode = graph['nodes'][aId]
		bNode = graph['nodes'][bId]
		kmDist = getDist(aNode, bNode)
		time = kmDist / kmPerHour

		edgeA = makeEdge(aId, bId, time, roadType, kmDist, time, roadName)
		aNode['edges'].append(edgeA)

		edgeB = makeEdge(bId, aId, time, roadType, kmDist, time, roadName)
		bNode['edges'].append(edgeB)

		graph['edges'].append(edgeA)

def makeEdge(startId, endId, weight, roadType, kmDist, time, roadName):
	edge = {}
	edge['start'] = startId
	edge['end'] = endId
	edge['weight'] = weight
	edge['type'] = roadType
	edge['kmDist'] = kmDist
	edge['time'] = time
	edge['roadName'] = roadName
	return edge

def getDist(aNode, bNode):
	# haversine distance
	lat1 = aNode['lat']
	lat2 = bNode['lat']
	lon1 = aNode['lon']
	lon2 = bNode['lon']
	dlon = lon2 - lon1 
	dlat = lat2 - lat1
	a = math.sin(dlat/2)**2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlon/2)**2
	c = 2 * math.asin(math.sqrt(a)) 
	km = 6367 * c
	return km

if __name__ == '__main__':
	run()