CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1061;
	title = 106102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 793;
				taid = 2;
				type = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 5;
				idx0 = -1;
				cnt0 = 0;
				ectype = -1;
				etype = 1;
				qtidx = -1;
				taid = 1;
				esctype = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;1;0;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 106107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8031401;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
			CDboTSCheckClrQst
			{
				and = "1060;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 106109;
				ctype = 1;
				idx = 8031401;
				taid = 2;
			}
			CDboTSActQItem
			{
				icnt0 = 1;
				iprob0 = "1.000000";
				iidx0 = 793;
				taid = 3;
				type = 0;
			}
			CDboTSActRegQInfo
			{
				cont = 106108;
				m1fx = "2153.000000";
				m2fz = "1353.000000";
				m1fy = "0.000000";
				sort = 106105;
				m2widx = 1;
				grade = 132203;
				m0fx = "2326.000000";
				m0ttip = 106115;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 106102;
				gtype = 1;
				area = 106101;
				goal = 106104;
				m0fz = "2190.000000";
				m0widx = 1;
				m1ttip = 106115;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "1708.000000";
				m2fx = "3051.000000";
				m2ttip = 106115;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 106114;
			nextlnk = 101;
			rwdtbl = 106101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8031401;
			}
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 5;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 106108;
			gtype = 1;
			oklnk = 2;
			area = 106101;
			goal = 106104;
			sort = 106105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 106102;
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 5;
				idx0 = 106101;
				cnt0 = 3;
				ectype = -1;
				etype = 0;
				qtidx = 106130;
				taid = 1;
				esctype = 0;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 793;
				taid = 1;
				type = 1;
			}
		}
	}
}

