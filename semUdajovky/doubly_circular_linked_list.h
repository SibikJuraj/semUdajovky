#pragma once

#include "structures/heap_monitor.h"
#include "structures/list/list.h"
#include "structures/structure_iterator.h"
#include "structures/ds_routines.h"

namespace structures
{

	template<typename T>
	class DoublyCircularLinkedListItem : public DataItem<T>
	{
	public:

		DoublyCircularLinkedListItem(T data);
		DoublyCircularLinkedListItem(const DoublyCircularLinkedListItem<T>& other);

		~DoublyCircularLinkedListItem();

		DoublyCircularLinkedListItem<T>* getNext();
		DoublyCircularLinkedListItem<T>* getPrevious();

		void setNext(DoublyCircularLinkedListItem<T>* next);
		void setPrevious(DoublyCircularLinkedListItem<T>* previous);


	private:

		DoublyCircularLinkedListItem<T>* next_;
		DoublyCircularLinkedListItem<T>* previous_;

	};


	template<typename T>
	class DoublyCircularLinkedList : public List<T>
	{
	public:

		DoublyCircularLinkedList();
		DoublyCircularLinkedList(const DoublyCircularLinkedList<T>& other);

		~DoublyCircularLinkedList();

		Structure* clone() const override;
		size_t size() const override;

		List<T>& operator=(const List<T>& other) override;
		DoublyCircularLinkedList<T>& operator=(const DoublyCircularLinkedList<T>& other);
		T& operator[](const int index) override;
		const T operator[](const int index) const override;

		void add(const T& data) override;
		void insert(const T& data, const int index) override;

		bool tryRemove(const T& data) override;
		T removeAt(const int index) override;

		int getIndexOf(const T& data) override;

		void clear() override;

		Iterator<T>* getBeginIterator() const override;
		Iterator<T>* getEndIterator() const override;

	private:

		size_t size_;

		DoublyCircularLinkedListItem<T>* first_;
		DoublyCircularLinkedListItem<T>* last_;
	private:

		DoublyCircularLinkedListItem<T>* getItemAtIndex(int index) const;

	private:
		class DoublyCircularLinkedListIterator : public Iterator<T>
		{
		public:

			DoublyCircularLinkedListIterator(DoublyCircularLinkedListItem<T>* position);

			~DoublyCircularLinkedListIterator();

			Iterator<T>& operator= (const Iterator<T>& other) override;

			bool operator!=(const Iterator<T>& other) override;

			const T operator*() override;

			Iterator<T>& operator++() override;
		private:
			DoublyCircularLinkedList<T>* position_;
		};
	};

	template<typename T>
	inline DoublyCircularLinkedListItem<T>::DoublyCircularLinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr),
		previous_(nullptr)
	{
	}

	template<typename T>
	inline DoublyCircularLinkedListItem<T>::DoublyCircularLinkedListItem(const DoublyCircularLinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_),
		previous_(other.previous_)
	{
	}

	template<typename T>
	inline DoublyCircularLinkedListItem<T>::~DoublyCircularLinkedListItem()
	{
		next_ = nullptr;
		previous_ = nullptr;
	}

	template<typename T>
	inline DoublyCircularLinkedListItem<T>* DoublyCircularLinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline DoublyCircularLinkedListItem<T>* DoublyCircularLinkedListItem<T>::getPrevious()
	{
		return previous_;
	}

	template<typename T>
	inline void DoublyCircularLinkedListItem<T>::setNext(DoublyCircularLinkedListItem<T>* next)
	{
		next_ = next;
	}

	template<typename T>
	inline void DoublyCircularLinkedListItem<T>::setPrevious(DoublyCircularLinkedListItem<T>* previous)
	{
		previous_ = previous;
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedList() :
		List<T>::List(),
		size_(0),
		first_(nullptr),
		last_(nullptr)
	{
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedList(const DoublyCircularLinkedList<T>& other) :
		DoublyCircularLinkedList()
	{
		*this = other;
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::~DoublyCircularLinkedList()
	{
		clear();
	}

	template<typename T>
	inline Structure* DoublyCircularLinkedList<T>::clone() const
	{
		return new DoublyCircularLinkedList<T>(*this);
	}

	template<typename T>
	inline size_t DoublyCircularLinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& DoublyCircularLinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const DoublyCircularLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>& DoublyCircularLinkedList<T>::operator=(const DoublyCircularLinkedList<T>& other)
	{

		if (this != &other)
		{
			clear();
			DoublyCircularLinkedListItem<T>* current = other.first_;

			while (current != nullptr)
			{
				add(current->accessData());
				current = current->getNext();
			}
			

		}
		return *this;
	}

	template<typename T>
	inline T& DoublyCircularLinkedList<T>::operator[](const int index)
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T DoublyCircularLinkedList<T>::operator[](const int index) const
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::add(const T& data)
	{

		DoublyCircularLinkedListItem<T>* newLinkedListItem = new DoublyCircularLinkedListItem<T>(data);

		if (size_ == 0)
		{
			newLinkedListItem->setNext(newLinkedListItem);
			newLinkedListItem->setPrevious(newLinkedListItem);

			first_ = newLinkedListItem;

		}
		else
		{
			newLinkedListItem->setPrevious(last_);
			newLinkedListItem->setNext(first_);

			first_->setPrevious(newLinkedListItem);
			last_->setNext(newLinkedListItem);
	
		}

		last_ = newLinkedListItem;
		size_++;
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::insert(const T& data, const int index)
	{

		if (index == size_)
		{
			add(data);
		}
		else
		{
			DoublyCircularLinkedListItem<T>* newLinkedListItem = new DoublyCircularLinkedListItem<T>(data);

			DoublyCircularLinkedListItem<T>* nextItem = getItemAtIndex(index);
			DoublyCircularLinkedListItem<T>* prevItem = nextItem->getPrevious();
			
			newLinkedListItem->setPrevious(prevItem);
			newLinkedListItem->setNext(nextItem);

			nextItem->setPrevious(newLinkedListItem);
			prevItem->setNext(newLinkedListItem);

			if (index == 0)
			{
				first_ = newLinkedListItem;
			}

			size_++;
		}

	}

	template<typename T>
	inline bool DoublyCircularLinkedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data);

		if (index != -1)
		{
			removeAt(index);
			return true;
		}
		else
		{
			return false;
		}


	}

	template<typename T>
	inline T DoublyCircularLinkedList<T>::removeAt(const int index)
	{

		DoublyCircularLinkedListItem<T>* deletedItem = nullptr;

		if (index == 0 && size_ > 0)
		{
			deletedItem = first_;
			

			if (last_ == deletedItem)
			{
				first_ = nullptr;
				last_ = nullptr;
			}
			else {
				first_ = first_->getNext();

				last_->setNext(first_);
				first_->setPrevious(last_);
			}
		}
		else
		{
			deletedItem = getItemAtIndex(index);

			deletedItem->getPrevious()->setNext(deletedItem->getNext());
			deletedItem->getNext()->setPrevious(deletedItem->getPrevious());

			if (last_ == deletedItem)
			{
				last_ = deletedItem->getPrevious();
			}
		}
		T result = deletedItem->accessData();
		delete deletedItem;
		size_--;
		return result;

	}

	template<typename T>
	inline int DoublyCircularLinkedList<T>::getIndexOf(const T& data)
	{

		int index = 0;
		DoublyCircularLinkedListItem<T>* current = first_;


		while (index != size_)
		{
			if (current->accessData() == data)
			{
				return index;
			}
			index++;
			current = current->getNext();
		}
		return -1;
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::clear()
	{
		DoublyCircularLinkedListItem<T>* current = first_;

		while (current != last_)
		{
			DoublyCircularLinkedListItem<T>* deleted = current;

			current = current->getNext();
			delete deleted;

		}
		delete current;


		first_ = last_ = nullptr;
		size_ = 0;

	}

	template<typename T>
	inline Iterator<T>* DoublyCircularLinkedList<T>::getBeginIterator() const
	{
		return NULL;
	}

	template<typename T>
	inline Iterator<T>* DoublyCircularLinkedList<T>::getEndIterator() const
	{
		return NULL;
	}

	template<typename T>
	inline DoublyCircularLinkedListItem<T>* DoublyCircularLinkedList<T>::getItemAtIndex(int index) const
	{

		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");

		DoublyCircularLinkedListItem<T>* current = nullptr;


		if (index > this->size() / 2)
		{
			current = last_;

			for (int i = size_ - 1; i > index; i--)
			{
				current = current->getPrevious();
			}
			
		}
		else
		{
			current = first_;

			for (int i = 0; i < index; i++)
			{
				current = current->getNext();
			}
		}
		return current;
	}




	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::DoublyCircularLinkedListIterator(DoublyCircularLinkedListItem<T>* position) :
		position_(position)
	{
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::~DoublyCircularLinkedListIterator()
	{
		position_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::operator=(const Iterator<T>& other)
	{
		const DoublyCircularLinkedListIterator& otherLLI = dynamic_cast<const DoublyCircularLinkedListIterator&>(other);
		position_ = otherLLI.position_;
		return *this;
	}

	template<typename T>
	inline bool DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::operator!=(const Iterator<T>& other)
	{
		const DoublyCircularLinkedListIterator& otherLLI = dynamic_cast<const DoublyCircularLinkedListIterator&>(other);
		return position_ != otherLLI.position_;
	}

	template<typename T>
	inline const T DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::operator*()
	{
		return position_->accessData();
	}

	template<typename T>
	inline Iterator<T>& DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::operator++()
	{
		position_ = position_->getNext();
		return *this;
	}



}