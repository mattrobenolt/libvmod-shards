Summary: Varnish Consistent Hashing
Name: vmod-shards
Version: 0.2
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
Source0: libvmod-shards.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish >= 4.0.2
BuildRequires: make
BuildRequires: python-docutils
BuildRequires: varnish >= 4.0.2
BuildRequires: varnish-libs-devel >= 4.0.2

%description
Varnish Consistent Hashing

%prep
%setup -n libvmod-shards-trunk

%build
%configure --prefix=/usr/
%{__make} %{?_smp_mflags}
%{__make} %{?_smp_mflags} check

%install
[ %{buildroot} != "/" ] && %{__rm} -rf %{buildroot}
%{__make} install DESTDIR=%{buildroot}

%clean
[ %{buildroot} != "/" ] && %{__rm} -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_libdir}/varnis*/vmods/
%doc /usr/share/doc/lib%{name}/*
%{_mandir}/man?/*

%changelog
* Tue Aug 30 2015 Ondrej Novy <ondrej.novy@firma.seznam.cz> - 0.2-0.20150830
- Varnish 4 support.
* Thu Jan 30 2014 Matt Robenolt <matt@ydekproductions.com> - 0.1-0.20140130
- Initial version.
