/*
 * OkcVisualMapResult.cpp
 *
 *  Created on: Jan 13, 2009
 *      Author: Zaixian Xie
 */

#include "visualmap/multidim/OkcVisualMapResult.h"

#include <typeinfo>
#include <assert.h>
#include <vector>

#include "visualmap/VisualAttribute.h"
#include "operator/brush/Brush.h"
#include "operator/brush/BrushOperator.h"
#include "operator/sbb/HierDisplayInformation.h"
#include "main/XmdvTool.h"
#include "data/Data.h"
#include "data/multidim/OkcData.h"
#include "color/ColorManager.h"
#include "visualmap/multidim/ScatterVisAttr.h"

OkcVisualMapResult::OkcVisualMapResult() :
	VisualMapResult() {
		m_scatterVisAttr = 0;
		diag_VisAttr = 0;
		inBrushVisAttr = 0;
		outBrushVisAttr = 0;
		initBrush();
		initGlyphPlaceResult();
		initHierParameters();
}

OkcVisualMapResult::OkcVisualMapResult(Data* input) :
	VisualMapResult(input) {
		m_scatterVisAttr = 0;
		diag_VisAttr = 0;
		inBrushVisAttr = 0;
		outBrushVisAttr = 0;
		assert ( typeid(*input) == typeid(OkcData) );
		OkcData* okcdata = dynamic_cast<OkcData*>(input);
		int dataSize = okcdata->getDataSize();
		if (dataSize>0) {
				this->clearDataVisAttr();
				this->data_VisAttr.resize(dataSize);
		}
		initBrush();
		initHierParameters();
}

OkcVisualMapResult::~OkcVisualMapResult() {
	SAFE_DELETE(m_brush);
	SAFE_DELETE(inBrushVisAttr);
	SAFE_DELETE(outBrushVisAttr);
	clearDataVisAttr();
}

void OkcVisualMapResult::initHierParameters() {
	m_bIsSBBResult = false;
	m_hier_info = 0;
}

int OkcVisualMapResult::getDataSize() {
	OkcData * okcdata = (OkcData*)getData();
	int data_size = okcdata->getDataSize();
	return data_size;
}

int OkcVisualMapResult::getDimSize() {
	OkcData * okcdata = (OkcData*)getData();
	int dim_size = okcdata->getDimSize();
	return dim_size;
}

void OkcVisualMapResult::getDataItem(std::vector<double> &buf, int line) {
	OkcData* okcdata = (OkcData*)getData();
	okcdata->getData(buf, line);
}

// get the dimension names
std::vector<char*> OkcVisualMapResult::getDimNameArr() {
	std::vector<char*> dimNames;
	OkcData * okcdata = dynamic_cast<OkcData*>(getData());
	okcdata->getDimNameArr(dimNames);
	return dimNames;
}

std::vector<double> OkcVisualMapResult::getDimMinArr(){
	std::vector<double> buf;
	OkcData * okcdata = dynamic_cast<OkcData*>(getData());
	okcdata->getDimMinArr(buf);
	return buf;
}

// get the maximum values for dimensions
std::vector<double> OkcVisualMapResult::getDimMaxArr() {
	std::vector<double> buf;
	OkcData * okcdata = dynamic_cast<OkcData*>(getData());
	okcdata->getDimMaxArr(buf);
	return buf;
}

void OkcVisualMapResult::setBrushOperator(BrushOperator* brushOperator) {
	this->m_brushOperator = brushOperator;
}

BrushOperator* OkcVisualMapResult::getBrushOperator() {
	return this->m_brushOperator;
}

void OkcVisualMapResult::setBrush(Brush* brush) {
	SAFE_DELETE(m_brush);
	m_brush = brush;
}

Brush* OkcVisualMapResult::getBrush() {
	return m_brush;
}

void OkcVisualMapResult::initBrush() {
	this->m_brushOperator = 0;
	this->m_brush = 0;

	SAFE_DELETE(inBrushVisAttr);
	this->inBrushVisAttr = new VisualAttribute(true);

	SAFE_DELETE(outBrushVisAttr);
	this->outBrushVisAttr = new VisualAttribute(false);
}

void OkcVisualMapResult::initGlyphPlaceResult() {
	m_glyphPlaceResult = 0;
}

void OkcVisualMapResult::setGlyphPlaceResult(GlyphPlaceResult* placeResult) {
	m_glyphPlaceResult = placeResult;
}

void OkcVisualMapResult::initDiagVisAttr() {
	diag_VisAttr = 0;
}

void OkcVisualMapResult::setDiagVisAttr(DiagVisAttr* _diag_VisAttr) {
	SAFE_DELETE(diag_VisAttr);
	diag_VisAttr = _diag_VisAttr;
}

GlyphPlaceResult* OkcVisualMapResult::getGlyphPlaceResult() {
	return m_glyphPlaceResult;
}

void OkcVisualMapResult::setGlyphShape(XmdvTool::GLYPHSHAPE shape) {
	m_glyphShape = shape;
}

XmdvTool::GLYPHSHAPE OkcVisualMapResult::getGlyphShape() {
	return m_glyphShape;
}

std::vector<VisualAttribute*> OkcVisualMapResult::getDataVisAttr() {
	return this->data_VisAttr;
}

ScatterVisAttr* OkcVisualMapResult::getScatterVisAttr() {
	return this->m_scatterVisAttr;
}

void OkcVisualMapResult::setScatterVisAttr(ScatterVisAttr* scatterVisAttr) {
	m_scatterVisAttr = scatterVisAttr;
}

VisualAttribute* OkcVisualMapResult::getInBrushVisAttr() {
	return this->inBrushVisAttr;
}

VisualAttribute* OkcVisualMapResult::getOutBrushVisAttr() {
	return this->outBrushVisAttr;
}

void OkcVisualMapResult::setDiagMultiDimDataVisAttr(VisualAttribute* VisAttr, int dim, int pos) {
	this->diag_VisAttr->multi_dim_data_VisAttr[dim][pos] = VisAttr;
}

VisualAttribute* OkcVisualMapResult::getDiagMultiDimDataVisAttr(int dim, int pos) {
	return this->diag_VisAttr->multi_dim_data_VisAttr[dim][pos];
}

void OkcVisualMapResult::setSingleDataVisAttr(VisualAttribute* VisAttr, int pos) {
	this->data_VisAttr[pos] = VisAttr;
}

VisualAttribute* OkcVisualMapResult::getSingleDataVisAttr(int pos) {
	return this->data_VisAttr[pos];
}

void OkcVisualMapResult::setSBBResult(bool isSBB) {
	m_bIsSBBResult = isSBB;
}

bool OkcVisualMapResult::isSBBResult() {
	return m_bIsSBBResult;
}

void OkcVisualMapResult::setHierInfo(HierDisplayInformation* hier_info) {
	m_hier_info = hier_info;
}

HierDisplayInformation* OkcVisualMapResult::getHierInfo() {
	return m_hier_info;
}

void OkcVisualMapResult::setCardinality(std::vector<int> card) {
	m_cardinality = card;
}

std::vector<int> OkcVisualMapResult::getCardinality() {
	return m_cardinality;
}

void OkcVisualMapResult::clearDataVisAttr(){
	for(std::vector<VisualAttribute*>::iterator it = data_VisAttr.begin(); it!=data_VisAttr.end(); ++it){
		SAFE_DELETE(*it);
	}
}
