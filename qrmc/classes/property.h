#pragma once

#include <QtCore/QString>

#include "../../qrrepo/repoApi.h"

namespace qrmc {
	class Property
	{
	public:
		Property(qrRepo::LogicalRepoApi *api, qReal::Id const &id);

		bool init();
		QString name() const;
		QString type() const;
		QString defaultValue() const;
		Property *clone();
		bool operator == (Property const &other) const;
		bool operator != (Property const &other) const;
		bool isReferenceProperty() const;
		void print() const;

		QString generatePropertyLine(const QString &lineTemplate) const;
		QString generateDefaultsLine(const QString &lineTemplate) const;
		QString generateDisplayedNameLine(const QString &lineTemplate) const;

	private:
		qrRepo::LogicalRepoApi *mApi;
		qReal::Id mId;
		QString mName;
		QString mType;
		bool mIsEnum;
		bool mIsReference;
		QString mDescription;
		QString mDefaultValue;
		QString mDisplayedName;
	};
}
