/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C)  Joseph Artsimovich <joseph.artsimovich@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SerializableSpline.h"
#include "EditableSpline.h"
#include "XmlMarshaller.h"
#include "XmlUnmarshaller.h"
#include <QTransform>
#include <boost/foreach.hpp>

SerializableSpline::SerializableSpline(const EditableSpline& spline) {
    SplineVertex::Ptr vertex(spline.firstVertex());
    for (; vertex; vertex = vertex->next(SplineVertex::NO_LOOP)) {
        m_points.push_back(vertex->point());
    }
}

SerializableSpline::SerializableSpline(const QDomElement& el) {
    const QString point_str("point");

    QDomNode node(el.firstChild());
    for (; !node.isNull(); node = node.nextSibling()) {
        if (!node.isElement()) {
            continue;
        }
        if (node.nodeName() != point_str) {
            continue;
        }

        m_points.push_back(XmlUnmarshaller::pointF(node.toElement()));
    }
}

SerializableSpline::SerializableSpline(const QPolygonF& polygon) {
    for (int i = polygon.size() - 1; i >= 0; i--) {
        m_points.push_back(polygon[i]);
    }
}

QDomElement SerializableSpline::toXml(QDomDocument& doc, const QString& name) const {
    QDomElement el(doc.createElement(name));

    const QString point_str("point");
    XmlMarshaller marshaller(doc);
    for (const QPointF& pt : m_points) {
        el.appendChild(marshaller.pointF(pt, point_str));
    }

    return el;
}

SerializableSpline SerializableSpline::transformed(const QTransform& xform) const {
    SerializableSpline transformed(*this);

    for (QPointF& pt : transformed.m_points) {
        pt = xform.map(pt);
    }

    return transformed;
}

SerializableSpline SerializableSpline::transformed(const boost::function<QPointF(const QPointF&)>& xform) const {
    SerializableSpline transformed(*this);

    for (QPointF& pt : transformed.m_points) {
        pt = xform(pt);
    }

    return transformed;
}
