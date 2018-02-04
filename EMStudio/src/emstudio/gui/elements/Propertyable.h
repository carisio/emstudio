/*
 * Propertyable.h
 *
 *  Created on: 03/09/2011
 *      Author: Leandro
 */

#ifndef PROPERTYABLE_H_
#define PROPERTYABLE_H_

#include <tr1/memory>
#include <list>
#include "Property.h"
#include "emstudio/exception/PropertyNotFoundException.h"
#include "emstudio/util/file/InputBuffer.h"
#include "emstudio/util/file/OutputBuffer.h"

using namespace::std;

class Propertyable;

typedef std::tr1::shared_ptr<Propertyable> PropertyableSmartPointer;

class Propertyable {
private:
	list<Property> propertyList;
	wxString allPropertiesTogetherErrorMessage;
	bool changed;
public:
	typedef list<Property>::iterator Iterator;

	Propertyable();
	virtual ~Propertyable();

	bool IsChanged();
	void SetChanged(bool c);

	virtual list<Property>* GetPropertiesList();
	void AddProperty(Property p);

	void TransferDataFrom(PropertyableSmartPointer objectFrom);
	virtual PropertyableSmartPointer NewPropertyable() = 0;
	virtual Property& GetProperty(wxString name) throw(PropertyNotFoundException);

	void WriteProperties(OutputBuffer& buffer);
	void ReadProperties(InputBuffer& buffer) throw(BaseTypeIncompatibleException, PropertyNotFoundException);

	/* Verifica os validadores vinculados a cada propriedade */
	bool IsPropertiesValid();
	wxString GetPropertiesErrorMessage();

	/* Verifica se as propriedades conjuntas fazem sentido. A diferen�a de IsAllPropertiesTogetherValid
	 * e IsPropertiesValid � que a �ltima testa a validade de um BaseType e a segunda testar�
	 * Nota importante: esses m�todos devem ser chamados apenas se as propriedades individuais
	 * j� foram validadas, ou seja, IsPropertiesValid() == true.
	 *
	 * A ideia aqui � a seguinte. IsAllPropertiesTogetherValid() � chamado para valida��o e, enquanto isso � feito,
	 * ele deve ir montando sua mensagem de erro. Quando a valida��o tiver sido terminada, deve chamar SetAllPropertiesTogetherErrorMessage()
	 * para configurar sua mensagem de erro.
	 */
	virtual bool IsAllPropertiesTogetherValid();
	void SetAllPropertiesTogetherErrorMessage(wxString msg);
	wxString GetAllPropertiesTogetherErrorMessage();
};

#endif /* PROPERTYABLE_H_ */
