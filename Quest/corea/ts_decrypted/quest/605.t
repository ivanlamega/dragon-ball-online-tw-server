CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 605;
	title = 60502;

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
				eitype = 3;
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
			stdiag = 60507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031203;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
			CDboTSCheckClrQst
			{
				and = "604;";
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
				conv = 60509;
				ctype = 1;
				idx = 3031203;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 521;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
			CDboTSActRegQInfo
			{
				cont = 60508;
				gtype = 2;
				area = 60501;
				goal = 60504;
				m0fz = "2376.000000";
				m0widx = 1;
				sort = 60505;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "6480.000000";
				m0ttip = 60515;
				rwd = 100;
				taid = 1;
				title = 60502;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 60514;
			nextlnk = 101;
			rwdtbl = 60501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031203;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 521;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 60508;
			gtype = 2;
			oklnk = 2;
			area = 60501;
			goal = 60504;
			sort = 60505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 60502;
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
				itype = 3;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 521;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 521;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 60507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

