CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 652;
	title = 65202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 65208;
				m1fx = "5475.000000";
				area = 65201;
				goal = 65204;
				m0fz = "698.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 65216;
				sort = 65205;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "832.000000";
				grade = 132203;
				m0fx = "6308.000000";
				m0ttip = 65215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 65202;
				gtype = 2;
			}
			CDboTSActNPCConv
			{
				conv = 65209;
				ctype = 1;
				idx = 1351203;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 13;
				eitype = 1;
				idx0 = 528;
				cnt0 = 13;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 529;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 65207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1351203;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckClrQst
			{
				and = "651;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 65208;
			gtype = 2;
			oklnk = 2;
			area = 65201;
			goal = 65204;
			sort = 65205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 65202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 65214;
			nextlnk = 101;
			rwdtbl = 65201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1351204;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 65207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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
				iidx1 = 529;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 528;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
	}
}

