CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 742;
	title = 74202;

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
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 74207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 3332202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 33;
				minlvl = 25;
			}
			CDboTSCheckClrQst
			{
				and = "741;";
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
				conv = 74209;
				ctype = 1;
				idx = 3332202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 74208;
				m1fx = "7404.000000";
				area = 74201;
				goal = 74204;
				m0fz = "-620.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 74216;
				sort = 74205;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-620.000000";
				grade = 132203;
				m0fx = "7404.000000";
				m0ttip = 74215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 74202;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 11;
				eitype = 1;
				idx0 = 559;
				cnt0 = 11;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 560;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 74208;
			gtype = 2;
			oklnk = 2;
			area = 74201;
			goal = 74204;
			sort = 74205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 74202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 74214;
			nextlnk = 101;
			rwdtbl = 74201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3332202;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iidx1 = 560;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 559;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 74207;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
	}
}

