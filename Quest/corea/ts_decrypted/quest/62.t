CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 62;
	title = 6202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 6209;
				ctype = 1;
				idx = 7091101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 6208;
				gtype = 0;
				area = 6201;
				goal = 6204;
				grade = 132203;
				rwd = 100;
				sort = 6205;
				stype = 1;
				taid = 1;
				title = 6202;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 6207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckPCCls
			{
				clsflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 7091101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 18;
				minlvl = 10;
			}
			CDboTSCheckClrQst
			{
				and = "59;";
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
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 6208;
			gtype = 0;
			oklnk = 2;
			area = 6201;
			goal = 6204;
			sort = 6205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 6202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 6214;
			nextlnk = 254;
			rwdtbl = 6201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4181101;
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
}

