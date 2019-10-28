CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6010;
	title = 601002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 601007;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
			CDboTSCheckPCCls
			{
				clsflg = 32;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6005;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 601009;
				ctype = 1;
				idx = 3031101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 601008;
				gtype = 1;
				area = 601001;
				goal = 601004;
				grade = -1;
				rwd = 100;
				sort = 601005;
				stype = 8;
				taid = 1;
				title = 601002;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 601008;
			gtype = 1;
			oklnk = 2;
			area = 601001;
			goal = 601004;
			sort = 601005;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 601002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 601014;
			nextlnk = 253;
			rwdtbl = 601001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4141101;
			}
		}
	}
}

