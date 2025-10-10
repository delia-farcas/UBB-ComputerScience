#pragma once
#include <QAbstractTableModel>
#include "Dog.h"
#include "user_repository.h"

class UserDogsModel : public QAbstractTableModel {
    Q_OBJECT
private:
    UserRepository& userRepo;

public:
    UserDogsModel(UserRepository& repo, QObject* parent = nullptr)
        : QAbstractTableModel(parent), userRepo(repo) {
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return userRepo.getAdoptionList().size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole) return QVariant{};

        const Dog& d = userRepo.getAdoptionList().at(index.row());
        switch (index.column()) {
        case 0: return QString::fromStdString(d.getName());
        case 1: return QString::fromStdString(d.getBreed());
        case 2: return QString::number(d.getAge());
        case 3: return QString::fromStdString(d.getPhotograph());
        default: return QVariant{};
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant{};

        switch (section) {
        case 0: return "Name";
        case 1: return "Breed";
        case 2: return "Age";
        case 3: return "Photo URL";
        default: return QVariant{};
        }
    }
};
