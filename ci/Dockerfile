FROM epitechcontent/epitest-docker

RUN dnf install ruby
RUN git clone https://github.com/ronanboiteau/NormEZ.git
RUN cp NormEZ/NormEZ.rb /usr/bin/NormEZ && chmod +x /usr/bin/NormEZ
RUN rm -rf NormEZ
RUN pip3 install mypy pycodestyle pydocstyle pytest
ADD integration_tester.py /usr/bin/integration_tester
RUN chmod +x /usr/bin/integration_tester
