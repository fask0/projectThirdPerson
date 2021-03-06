#include <iostream>

#include "GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameController.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"

#include "mge/config.hpp"

GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition)
	: _name(pName), _transform(glm::translate(pPosition)), _parent(nullptr), _children(),
	_mesh(nullptr), _behaviour(nullptr), _material(nullptr), _world(nullptr)

{
	isColliding = false;
	_shouldDie = false;
	GameController::GameObjects.push_back(this);
	_gameControllerIndex = GameController::GameObjects.size() - 1;
}

GameObject::~GameObject()
{
	//detach all children
	std::cout << "GC running on: " << _name;
	removeAllBehaviours();
	_parent->remove(this);

	while (_children.size() > 0)
	{
		GameObject* child = _children[0];
		remove(child);
		delete child;
	}
	if (_material != nullptr && dynamic_cast<LitDynamicTextureGridMaterial*>(_material))
	{
		delete _material;
		_material = nullptr;
	}

	std::cout << " | Deleted: " << _name << std::endl;
	//do not forget to delete behaviour, material, mesh, collider manually if required!
}

void GameObject::setName(const std::string& pName)
{
	_name = pName;
}

std::string GameObject::getName() const
{
	return _name;
}

void GameObject::setTransform(const glm::mat4& pTransform)
{
	_transform = pTransform;
}

const glm::mat4& GameObject::getTransform() const
{
	return _transform;
}

void GameObject::setLocalPosition(glm::vec3 pPosition)
{
	_lastPosition = glm::vec3(_transform[3]);
	_transform[3] = glm::vec4(pPosition, 1);
}

glm::vec3 GameObject::getLocalPosition() const
{
	return glm::vec3(_transform[3]);
}

void GameObject::removeMaterial()
{
	_material = nullptr;
}

void GameObject::setMaterial(AbstractMaterial* pMaterial)
{
	_material = pMaterial;
}

AbstractMaterial * GameObject::getMaterial() const
{
	return _material;
}

void GameObject::setMesh(Mesh* pMesh)
{
	_mesh = pMesh;
}

Mesh * GameObject::getMesh() const
{
	return _mesh;
}

void GameObject::setBehaviour(AbstractBehaviour* pBehaviour)
{
	_behaviour = pBehaviour;
	_behaviour->setOwner(this);
}

AbstractBehaviour* GameObject::getBehaviour() const
{
	return _behaviour;
}

void GameObject::addBehaviour(AbstractBehaviour* pBehaviour)
{
	_behaviours.push_back(pBehaviour);
	_behaviours.back()->setOwner(this);
}

void GameObject::removeBehaviour(AbstractBehaviour* pBehaviour)
{
	for (int i = 0; i < _behaviours.size(); i++)
	{
		if (_behaviours[i] == pBehaviour)
		{
			_behaviours.erase(_behaviours.begin() + i);
		}
	}
}

void GameObject::removeBehaviourAtIndex(int pIndex)
{
	delete(_behaviours[pIndex]);
	_behaviours.erase(_behaviours.begin() + pIndex);
}

void GameObject::removeAllBehaviours()
{
	for each (AbstractBehaviour* behaviour in _behaviours)
	{
		delete(behaviour);
	}
	_behaviours.clear();
}

std::vector<AbstractBehaviour*> GameObject::getBehaviours() const
{
	return _behaviours;
}

void GameObject::setParent(GameObject* pParent)
{
	//remove from previous parent
	if (_parent != nullptr)
	{
		_parent->_innerRemove(this);
	}

	//set new parent
	if (pParent != nullptr)
	{
		pParent->_innerAdd(this);
	}

	//if we have been detached from our parent, make sure
	//the world reference for us and all our children is set to null
	//if we have been attached to a parent, make sure
	//the world reference for us and all our children is set to our parent world reference
	//(this could still be null if the parent or parent's parent is not attached to the world)
	if (_parent == nullptr)
	{
		_setWorldRecursively(nullptr);
	}
	else
	{
		//might still not be available if our parent is not part of the world
		_setWorldRecursively(_parent->_world);
	}
}

void GameObject::_innerRemove(GameObject* pChild)
{
	for (auto i = _children.begin(); i != _children.end(); ++i)
	{
		if (*i == pChild)
		{
			_children.erase(i);
			pChild->_parent = nullptr;
			return;
		}
	}
}

void GameObject::_innerAdd(GameObject* pChild)
{
	_children.push_back(pChild);
	pChild->_parent = this;
}

void GameObject::add(GameObject* pChild)
{
	pChild->setParent(this);
}

void GameObject::remove(GameObject* pChild)
{
	pChild->setParent(nullptr);
}

GameObject* GameObject::getParent() const
{
	return _parent;
}

////////////

//costly operation, use with care
glm::vec3 GameObject::getWorldPosition() const
{
	return glm::vec3(getWorldTransform()[3]);
}

//costly operation, use with care
glm::mat4 GameObject::getWorldTransform() const
{
	if (_parent == nullptr) return _transform;
	else return _parent->getWorldTransform() * _transform;
}

////////////

void GameObject::translate(glm::vec3 pTranslation)
{
	setTransform(glm::translate(_transform, pTranslation));
}

void GameObject::scale(glm::vec3 pScale)
{
	setTransform(glm::scale(_transform, pScale));
	for each (AbstractBehaviour* behaviour in _behaviours)
	{
		if (dynamic_cast<CollisionBehaviour*>(behaviour) != nullptr)
		{
			dynamic_cast<CollisionBehaviour*>(behaviour)->ScaleCollider(pScale[0] * 2);
		}
	}
}

void GameObject::rotate(float pAngle, glm::vec3 pAxis)
{
	setTransform(glm::rotate(_transform, pAngle, pAxis));
}

void GameObject::update(float pStep)
{
	if (_shouldDie)
	{
		delete(this);
		return;
	}

	//make sure behaviour is updated after worldtransform is set
	if (_behaviour)
	{
		_behaviour->update(pStep);
	}

	for (int i = 0; i < _behaviours.size(); i++)
	{
		_behaviours[i]->update(pStep);
	}

	for (int i = _children.size() - 1; i >= 0; --i)
	{
		_children[i]->update(pStep);
	}
}

void GameObject::_setWorldRecursively(World* pWorld)
{
	_world = pWorld;

	for (int i = _children.size() - 1; i >= 0; --i)
	{
		_children[i]->_setWorldRecursively(pWorld);
	}
}

int GameObject::getChildCount() const
{
	return _children.size();
}

GameObject* GameObject::getChildAt(int pIndex) const
{
	return _children[pIndex];
}

glm::vec3 GameObject::getLastPosition()
{
	return _lastPosition;
}

void GameObject::OnCollisionEnter(GameObject* pOther)
{
}

void GameObject::OnCollisionStay(GameObject* pOther)
{
}

void GameObject::OnCollisionExit(GameObject* pOther)
{
}

bool GameObject::SkipCollisionCheck()
{
	return true;
}

bool GameObject::IgnoreCollision(GameObject * pOther)
{
	for (int i = 0; i < _ignoreTags.size(); ++i)
		if (_ignoreTags[i].compare(pOther->GetTag()) == 0)
			return true;

	return false;
}

void GameObject::SetTag(std::string pTag)
{
	_tag = pTag;
}

std::string GameObject::GetTag()
{
	return _tag;
}

void GameObject::Kill()
{
	_shouldDie = true;
}
